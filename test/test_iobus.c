// test_iobus.c
// by ccfreak2k
// public domain

// The purpose of this file is to both test and demonstrate the use of the
// I/O expander. When properly functioning, it should shift an active signal
// through all the wires, starting at white and incrementing every half second.

// If you're running this without modification in the emulator, put the I/O
// expander in slot 3.

#include <conio.h>

// To use an I/O extender, include these headers
//#include <mmu.h>
#include <peekpoke.h>

// These are the colored wires and their associated bitwise values.
// IO_OFF isn't really necessary, it's just there for completeness.
#define IO_OFF     0x0000
#define IO_WHITE   0x0001
#define IO_ORANGE  0x0002
#define IO_MAGENTA 0x0004
#define IO_LBLUE   0x0008
#define IO_YELLOW  0x0010
#define IO_LIME    0x0020
#define IO_PINK    0x0040
#define IO_GRAY    0x0080
#define IO_LGRAY   0x0100
#define IO_CYAN    0x0200
#define IO_PURPLE  0x0400
#define IO_BLUE    0x0800
#define IO_BROWN   0x1000
#define IO_GREEN   0x2000
#define IO_RED     0x4000
#define IO_BLACK   0x8000

extern void setMappedRedbusDevice(unsigned char);
extern void enableRedbus();

static char wai_fn[] = {
	0xCB, // wai
	0x60  // rts
};

// FIXME: Needed for now, remove when defined elsewhere.
#define kbhit() ( PEEK(0x304) != PEEK(0x305) )

// There's probably a better way to do this, but you get the idea here. Each WAI
// halts until the next game tick.
#define WAIT_HALFSEC() \
	__asm__ ("jsr %v", wai_fn); \
	__asm__ ("jsr %v", wai_fn); \
	__asm__ ("jsr %v", wai_fn); \
	__asm__ ("jsr %v", wai_fn); \
	__asm__ ("jsr %v", wai_fn); \
	__asm__ ("jsr %v", wai_fn); \
	__asm__ ("jsr %v", wai_fn); \
	__asm__ ("jsr %v", wai_fn); \
	__asm__ ("jsr %v", wai_fn); \
	__asm__ ("jsr %v", wai_fn);

int main() {
	int i = 1;
	int reg = 0x302;

	enableRedbus();
	setMappedRedbusDevice(1);
	cputs("I/O Expander test, setting device to 3 and running...\n");
	setMappedRedbusDevice(3);

	for (;;) {
		POKE(0x303,0x0000);
		POKE(0x302,0x0001);
		WAIT_HALFSEC();
		POKE(0x302,0x0002);
		WAIT_HALFSEC();
		POKE(0x302,0x0004);
		WAIT_HALFSEC();
		POKE(0x302,0x0008);
		WAIT_HALFSEC();
		POKE(0x302,0x0010);
		WAIT_HALFSEC();
		POKE(0x302,0x0020);
		WAIT_HALFSEC();
		POKE(0x302,0x0040);
		WAIT_HALFSEC();
		POKE(0x302,0x0080);
		WAIT_HALFSEC();
		POKE(0x302,0x0000);
		POKE(0x303,0x0001);
		WAIT_HALFSEC();
		POKE(0x303,0x0002);
		WAIT_HALFSEC();
		POKE(0x303,0x0004);
		WAIT_HALFSEC();
		POKE(0x303,0x0008);
		WAIT_HALFSEC();
		POKE(0x303,0x0010);
		WAIT_HALFSEC();
		POKE(0x303,0x0020);
		WAIT_HALFSEC();
		POKE(0x303,0x0040);
		WAIT_HALFSEC();
		POKE(0x303,0x0080);
		WAIT_HALFSEC();
	}
	// for (;;) {
		// POKE(reg,i);
		// __asm__ ("jsr %v", wai_fn);
		// if ( i == 0x80 ) {
			// i = 1;
			// reg = (reg == 0x302 ? 0x303 : 0x302);
		// }
		// else i <<= 1;
	// }

	return 0;
}