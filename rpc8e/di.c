// di.c
// an implementation of high-level disk drive access

// TODO: Emit error codes such as DI_DRIVE_NOT_READY

#include <stdint.h>
#include <string.h>

// Drive interface ready indicator
uint8_t di_rdy         = 0;

// Drive iface offset in memory, needs to be set before using
void   *di_offset      = 0x0;

// External memory buffer indicator
uint8_t di_useextbuf   = 0;

// Memory buffer to read/write data
void   *di_externalbuf = 0x0;

// Convenience macros
#define DI_EXTBUF  ((uint8_t *)di_externalbuf)
#define DI_BUFFER  ((uint8_t *)di_offset)
#define DI_SECTOR  ((uint16_t *)di_offset)[0x40]
#define DI_COMMAND ((uint8_t *)di_offset)[0x82]

#define DI_CMD_READ_DISK_NAME    1
#define DI_CMD_WRITE_DISK_NAME   2
#define DI_CMD_READ_DISK_SERIAL  3
#define DI_CMD_READ_DISK_SECTOR  4
#define DI_CMD_WRITE_DISK_SECTOR 5

#define DI_STATUS_READY          0
#define DI_STATUS_FAILURE        0xFF

int di_init ( void *offset ) {
	if (offset == 0)
		di_rdy = 0;
	else {
		di_offset = offset;
		di_rdy = 1;
	}
	return 0;
}

// TODO: basic check for the presence of a disk before attempting
int di_read ( uint16_t sec ) {
	if (di_rdy == 0) return 1;

	// FIXME: is this right? MSB needs to be in 0x81
	DI_SECTOR = sec;
	DI_COMMAND = DI_CMD_READ_DISK_SECTOR;

	// Wait for the drive to complete
	// FIXME: a while block would do better here.
	for (;;) if (DI_COMMAND != DI_CMD_READ_DISK_SECTOR) break;

	if (DI_COMMAND == DI_STATUS_FAILURE)
		return 2;

	// Copy the data out after reading
	if (di_useextbuf)
		memcpy(DI_EXTBUF, DI_BUFFER, 0x80);

	return 0;
}

// TODO: basic check for the presence of a disk before attempting
int di_write ( uint16_t sec ) {
	if (di_rdy == 0) return 1;

	// Copy the data in before writing
	if (di_useextbuf)
		memcpy(DI_BUFFER, DI_EXTBUF, 0x80);

	// FIXME: is this right? MSB needs to be in 0x81
	DI_SECTOR = sec;
	DI_COMMAND = DI_CMD_WRITE_DISK_SECTOR;

	// Wait for the drive to complete
	// FIXME: a while block would do better here.
	for (;;) if (DI_COMMAND != DI_CMD_WRITE_DISK_SECTOR) break;

	if (DI_COMMAND == DI_STATUS_FAILURE)
		return 2;

	return 0;
}

void di_setbuf ( void *buf ) {
	if (buf == 0) { 
		di_externalbuf = di_offset;
		di_useextbuf = 0;
	}
	else {
		di_externalbuf = buf;
		di_useextbuf = 1;
	}
}

void *di_getbuf ( void ) {
	return di_externalbuf;
}