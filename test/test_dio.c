// test_dio.c
// made by ccfreak2k
// released to the public domain

// The purpose of this code is to demonstrate/test the ability to read from, and
// write to, a disk. For simplicity, the disk is assumed to be ID 2, which is
// the default for a newly-spawned disk drive. It should detect the presence (or
// lack thereof) of a disk, print its serial number and verify a write on the
// first sector of the disk. This is a destructive write, so be sure to use a
// blank disk!

#include <conio.h>
#include <dio.h>
#include <string.h>
#include <peekpoke.h>
#include <stdio.h>
#include <errno.h>
#include "mmu.h"

extern void setMappedRedbusDevice(unsigned char);
unsigned char getRedbusWindowOffset( void );
extern void enableRedbus();

#define kbhit() ( PEEK(0x304) != PEEK(0x305) )

dhandle_t handle;

unsigned char testbufa[0x80];
unsigned char testbufb[0x80];
unsigned char cmpval[8];

int main() {
	int status;

	enableRedbus();
	setMappedRedbusDevice(1);

	cputs("Disk test, insert a BLANK disk and press any key to begin\n");
	while (!kbhit());

	cputs("Opening...");
	handle = dio_open(2);
	if (handle < 0) {
		cputs("failed!\n");
		return 1;
	}

	memset(testbufa,0xAA,0x80);
	memset(testbufb,0x55,0x80);

	cputs("success, performing write...");
	status = dio_write(handle,0,testbufa);
	if (status != 0) {
		cputs("failed!");
		return 1;
	}

	cputs("read...");
	status = dio_read(handle,0,testbufb);
	if (status != 0) {
		cputs("failed!\n");
		return 1;
	} else if (memcmp(testbufa,testbufb,0x80) != 0) {
		sprintf(cmpval,"%i",memcmp(testbufa,testbufb,0x80));
		cputs("cmp failed, value was ");
		cputs(cmpval);
		cputs("\n");
		return 1;
	}

	cputs("verify...");
	memset(testbufa,0x55,0x80);
	status = dio_write_verify(handle,0,testbufa);
	if (status != 0) {
		cputs("failed: ");
		switch (status) {
			case EIO:
				cputs("EIO");
				break;
			case EAGAIN:
				cputs("EAGAIN");
				break;
			case EUNKNOWN:
				cputs("EUNKNOWN");
				break;
			default:
				cputs("N/A (");
				sprintf(cmpval,"%i",status);
				cputs(cmpval);
				cputs(")");
				break;
		}
		cputs("\n");
		return 1;
	}

	cputs("complete.\n");

	return 0;
}
