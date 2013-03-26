// dio.c
// an implementation of cc65's DIO interface

// TODO: Disallow multiple opens on a single drive

#include <string.h>
#include <dio.h>
#include <stdint.h>
#include <errno.h>
#include "../include/mmu.h"
#include <conio.h>

void __fastcall__ setMappedRedbusDevice( unsigned char deviceId );
unsigned char getMappedRedbusDevice( void );
unsigned char getRedbusWindowOffset( void );
extern unsigned char __fastcall__ _seterrno (unsigned char code);

struct __dhandle_t {
	uint8_t id; // Drive ID
};

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

// errno.h doesn't have EOK so I just add it here.
#define	EOK 0

#define RB_PROLOGUE() \
	unsigned char old_device_id = getMappedRedbusDevice(); \
	void *rbw_offset = (void*)(getRedbusWindowOffset()<<8); \
	setMappedRedbusDevice(drive_id)

#define RB_EPILOGUE() \
	setMappedRedbusDevice(old_device_id)

#define DONE(val) \
	_seterrno(val); \
	return val

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

	RB_EPILOGUE();

	// Act
	// FIXME: os error codes should be set to what is most appropriate
	switch (status) {
		case DI_STATUS_SUCCESS:
			_seterrno(EOK);
			return (dhandle_t)drive_id;
		case DI_STATUS_FAILURE:
			_seterrno(EIO);
			return (dhandle_t)NULL;
		default:
			_seterrno(ENODEV);
			return (dhandle_t)NULL;
	}

	// It should never get here, but let's handle it anyway.
	_seterrno(EUNKNOWN);
	return (dhandle_t)NULL;
}

// Nothing needs to be done.
unsigned char __fastcall__ dio_close (dhandle_t handle) {
	DONE(EOK);
}

// Read a sector into a buffer
unsigned char __fastcall__ dio_read(dhandle_t handle, sectnum_t sect_num, void *buffer) {
	driveid_t drive_id = (driveid_t)handle;
	uint8_t   status;

	RB_PROLOGUE();

	if (DI_COMMAND != DI_STATUS_READY) {
		RB_EPILOGUE();
		DONE(EAGAIN);
	}

	DI_SECTOR = sect_num;
	DI_COMMAND = DI_CMD_READ_DISK_SECTOR;
	while (DI_COMMAND == DI_CMD_READ_DISK_SECTOR) continue;
	status = DI_COMMAND;

	switch (status) {
		case DI_STATUS_FAILURE:
			RB_EPILOGUE();
			DONE(EIO);
		case DI_STATUS_SUCCESS:
			memcpy(buffer, DI_BUFFER, 0x80);
			RB_EPILOGUE();
			DONE(EOK);
		default:
			RB_EPILOGUE();
			DONE(EUNKNOWN);
	}

	// It should never get here, but let's handle it anyway.
	DONE(EUNKNOWN);
}

unsigned char __fastcall__ dio_write(dhandle_t handle, sectnum_t sect_num, const void *buffer) {
	driveid_t drive_id = (driveid_t)handle;
	uint8_t   status;

	RB_PROLOGUE();

	if (DI_COMMAND != DI_STATUS_READY) {
		RB_EPILOGUE();
		DONE(EAGAIN);
	}

	memcpy(DI_BUFFER, buffer, 0x80);
	DI_SECTOR = sect_num;
	DI_COMMAND = DI_CMD_WRITE_DISK_SECTOR;
	while (DI_COMMAND == DI_CMD_WRITE_DISK_SECTOR) continue;
	status = DI_COMMAND;

	RB_EPILOGUE();

	switch (status) {
		case DI_STATUS_FAILURE:
			DONE(EIO);
		case DI_STATUS_SUCCESS:
			DONE(EOK);
		default:
			DONE(EUNKNOWN);
	}

	// It should never get here, but let's handle it anyway.
	DONE(EUNKNOWN);
}

unsigned char __fastcall__ dio_write_verify(dhandle_t handle, sectnum_t sect_num, const void *buffer) {
	unsigned char temp_buf[0x80];

	unsigned char status = dio_write(handle,sect_num,buffer);
	if (status != EOK)
		return status;

	status = dio_read(handle,sect_num,temp_buf);
	if (status != EOK)
		return status;

	if (memcmp(temp_buf,buffer,0x80) != 0) {
		DONE(EIO);
	} else {
		DONE(EOK);
	}
}

// FIXME: Implement
unsigned char __fastcall__ dio_phys_to_log(dhandle_t handle, const dio_phys_pos *physpos, sectnum_t *sectnum) {
	// sectnum = physpos.sector;

	// DONE(EOK);
	DONE(ENOSYS);
}

// FIXME: Implement
unsigned char __fastcall__ dio_log_to_phys(dhandle_t handle, const sectnum_t *sectnum, dio_phys_pos *physpos) {
	// physpos.head   = 0;
	// physpos.track  = 0;
	// physpos.sector = sectnum;

	// DONE(EOK);
	DONE(ENOSYS);
}
