// dio.c
// an implementation of cc65's DIO interface

#include <string.h>
#include <mmu.h>

// Convenience macros
//#define DI_EXTBUF  ((uint8_t *)di_externalbuf)
#define DI_BUFFER  ((uint8_t *)rbw_offset)
#define DI_SECTOR  ((uint16_t *)rbw_offset)[0x40]
#define DI_COMMAND ((uint8_t *)rbw_offset)[0x82]

#define DI_CMD_READ_DISK_NAME    1
#define DI_CMD_WRITE_DISK_NAME   2
#define DI_CMD_READ_DISK_SERIAL  3
#define DI_CMD_READ_DISK_SECTOR  4
#define DI_CMD_WRITE_DISK_SECTOR 5

#define DI_STATUS_READY          0
#define DI_STATUS_SUCCESS        0
#define DI_STATUS_FAILURE        0xFF

#define RB_PROLOGUE() \
	unsigned char old_device_id = getMappedRedbusDevice(); \
	void *rbw_offset = (getRedbusWindowOffset()<<8); \
	setMappedRedbusDevice(drive_id);

#define RB_EPILOGUE() \
	setMappedRedbusDevice(old_device_id);

// Notes:

// * We don't really need any state data, so the handle is just the drive ID.

// * RB_PROLOGUE() and RB_EPILOGUE() are convenience function macros to
// change/restore the redbus ID being addressed. Use at the beginning and end of
// a function, respectively; see dio_open() for an example.

// drive_id shall be the slave ID
// We will need to check two things:
// 1) is the slave ID a disk drive?
// 2) is a disk present in the drive?
// With the default rpc8e setup, the drive ID is 0. I think.
// By default a disk drive spawns with ID 2.

sectsize_t __fastcall__ dio_query_sectsize(dhandle_t handle) {
	return 128;
}

// FIXME: Should this return the actual number of allocated sectors instead?
sectnum_t __fastcall__ dio_query_sectcount(dhandle_t handle) {
	return 2049;
}

dhandle_t __fastcall__ dio_open (driveid_t drive_id) {
	uint8_t status;

	RB_PROLOGUE();

	// Try to read the disk serial number, we don't care what it is, just that
	// it succeeds.
	DI_COMMAND = DI_CMD_READ_DISK_SERIAL;
	// FIXME: This will probably hang if this isn't a drive, so we need a
	// timeout.
	while (DI_COMMAND == DI_CMD_READ_DISK_SERIAL) continue;
	status = DI_COMMAND;

	RB_EPOLOGUE();

	// Act
	switch (status) {
		case DI_STATUS_FAILURE:
			return -1;
		case DI_STATUS_SUCCESS:
			return (dhandle_t)drive_id;
		default:
			return -1;
	}

	return -1;
}

// Nothing needs to be done.
unsigned char __fastcall__ dio_close (dhandle_t handle) {
	return 0;
}

// Read a sector into a buffer
unsigned char __fastcall__ dio_read(dhandle_t handle, sectnum_t sect_num, void *buffer) {
	driveid_t drive_id = (driveid_t)handle;
	uint8_t   status;

	RB_PROLOGUE();

	if (DI_COMMAND != DI_STATUS_READY) {
		RB_EPILOGUE();
		return -1;
	}

	DI_SECTOR = sect_num;
	DI_COMMAND = DI_CMD_READ_DISK_SECTOR;
	while (DI_COMMAND == DI_CMD_READ_DISK_SECTOR) continue;
	status = DI_COMMAND;

	RB_EPILOGUE();

	switch (status) {
		case DI_STATUS_FAILURE:
			return -1;
		case DI_STATUS_SUCCESS:
			memcpy(buffer, DI_BUFFER, 0x80);
			return 0;
		default:
			return -1;
	}

	return -1;
}

unsigned char __fastcall__ dio_write(dhandle_t handle, sectnum_t sect_num, const void *buffer) {
	driveid_t drive_id = (driveid_t)handle;
	uint8_t   status;

	RB_PROLOGUE();

	if (DI_COMMAND != DI_STATUS_READY) {
		RB_EPILOGUE();
		return -1;
	}

	memcpy(DI_BUFFER, buffer, 0x80);
	DI_SECTOR = sect_num;
	DI_COMMAND = DI_CMD_WRITE_DISK_SECTOR;
	while (DI_COMMAND == DI_CMD_WRITE_DISK_SECTOR) continue;
	status = DI_COMMAND;

	RB_EPILOGUE();

	switch (status) {
		case DI_STATUS_FAILURE:
			return -1;
		case DI_STATUS_SUCCESS:
			return 0;
		default:
			return -1;
	}

	return -1;
}

unsigned char __fastcall__ dio_write_verify(dhandle_t handle, sectnum_t sect_num, const void *buffer) {
	char temp_buf[0x80];

	uint8_t status = dio_write(handle,sect_num,buffer);
	if (status != 0)
		return status;

	status = dio_read(handle,sect_num,temp_buf);
	if (status != 0)
		return status;

	status = memcmp(buffer,temp_buf,0x80);
	if (status != 0)
		return -1;

	return 0;
}


unsigned char __fastcall__ dio_phys_to_log(dhandle_t handle, const dio_phys_pos *physpos, sectnum_t *sectnum) {
	sectnum = dio_phys_pos.sector;

	return 0;
}

unsigned char __fastcall__ dio_log_to_phys(dhandle_t handle, const sectnum_t *sectnum, dio_phys_pos *physpos) {
	dio_phys_pos.head   = 0;
	dio_phys_pos.track  = 0;
	dio_phys_pos.sector = sectnum;

	return 0;
}
