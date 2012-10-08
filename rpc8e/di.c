// di.c
// an implementation of high-level disk drive access

// TODO: Emit error codes such as DI_DRIVE_NOT_READY

#include <stdint.h>
#include <di.h>

// Drive interface ready indicator
uint8_t   di_rdy       = 0;

// Drive iface offset in memory, needs to be set before using
uintptr_t di_offset    = 0x0;
#define   di_window di_offset

// External memory buffer indicator
uint8_t   di_useextbuf = 0;

// Memory buffer to read/write data
uintptr_t di_buf       = 0x0;

// Convenience macros
#define DI_BUFFER  di_offset
#define DI_SECTOR  di_offset[0x80]
#define DI_COMMAND di_offset[0x82]

#define DI_CMD_READ_DISK_NAME    1
#define DI_CMD_WRITE_DISK_NAME   2
#define DI_CMD_READ_DISK_SERIAL  3
#define DI_CMD_READ_DISK_SECTOR  4
#define DI_CMD_WRITE_DISK_SECTOR 5

#define DI_STATUS_READY          0
#define DI_STATUS_FAILURE        0xFF

int di_init ( int offset ) {
	if (offset == 0)
		di_rdy = 0;
	else {
		di_offset = offset;
		di_rdy = 1;
	}
	return 0;
}

// TODO: basic check for the presence of a disk before attempting
int di_read ( int sec ) {
	int i;

	if (di_rdy == 0) return 1;

	// FIXME: is this right? MSB needs to be in 0x81
	DI_SECTOR = sec;
	DI_COMMAND = DI_CMD_READ_DISK_SECTOR;

	// Wait for the drive to complete
	while (DI_COMMAND == DI_CMD_READ_DISK_SECTOR) do {}

	if (DI_COMMAND == DI_STATUS_FAILURE)
		return 2;

	// Copy the data out after reading
	if (di_useextbuf) {
		for (i = 0; i < 0x80; i++)
			di_buf[i] = DI_WINDOW[i];
	}

	return 0;
}

// TODO: basic check for the presence of a disk before attempting
int di_write ( int sec ) {
	int i;

	if (di_rdy == 0) return 1;

	// Copy the data in before writing
	if (di_useextbuf) {
		for (i = 0; i < 0x80; i++)
			DI_WINDOW[i] = di_buf[i];
	}

	// FIXME: is this right? MSB needs to be in 0x81
	DI_SECTOR = sec;
	DI_COMMAND = DI_CMD_WRITE_DISK_SECTOR;

	// Wait for the drive to complete
	while (DI_COMMAND == DI_CMD_WRITE_DISK_SECTOR) do {}

	if (DI_COMMAND == DI_STATUS_FAILURE)
		return 2;

	return 0;
}

void di_setbuf ( uintptr_t buf ) {
	if (buf == 0) { 
		di_buf = di_offset;
		di_useextbuf = 0;
	}
	else {
		di_buf = buf;
		di_useextbuf = 1;
	}
}

uintptr_t di_getbuf ( void ) {
	return di_buf;
}