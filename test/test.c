// -----------------------------------------------------------------------------
// test.c
//
// Barebones test main() for cc65-rpc8e
// -----------------------------------------------------------------------------
//
// Copyright (C) 2012 L. Adamson
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.
//
//  L. Adamson leaf@dizzydragon.net
//

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <peekpoke.h>
#include <time.h>

#include <unistd.h>
#include <fcntl.h>

extern void setMappedRedbusDevice(unsigned char);
extern unsigned getMappedRedbusDevice();
extern void enableRedbus();
extern void disableRedbus();

#define	RedBusOff		0
#define RedBusWhite		1
#define RedBusOrange	2
#define RedBusMagenta	4
#define RedBusLightBlue 8
#define RedBusYellow	16
#define RedBusLime		32
#define RedBusPink		64
#define RedBusGray		128
#define RedBusLightGray	256
#define RedBusCyan		512
#define RedBusPurple	1024
#define RedBusBlue		2048
#define RedBusBrown		4096
#define RedBusGreen		8192
#define RedBusRed		16384
#define RedBusBlack		32768

// FIXME: kbhit() defined here because conio.h is not written at this time
// make sure to remove this def of kbhit() if it's added later
#define kbhit() ( PEEK(0x304) != PEEK(0x305) )

void setCursorMode(short mode)
{
	POKE( 0x303, mode );
}

int main()
{
    unsigned char c;
	unsigned char i = RedBusWhite;
	
	enableRedbus();
	
	setMappedRedbusDevice(3);
	POKE( 0x302, 0 ); //reset iox
	
	setMappedRedbusDevice(1);
	
	setCursorMode(1);
	clrscr();
	cputs( "Hello, World of C!\nBegin input loop: ");
	
	setCursorMode(2);
	
	//setMappedRedbusDevice(3);
	
	//POKE( 0x302, RedBusWhite | RedBusOrange | RedBusMagenta | RedBusLightBlue); // set io expander bits
	
	while(1)
	{
		
		if (kbhit())
		{
			c = cgetc();
			
			if (c == '\r')
			{
				gotoxy(0, wherey()+1);
			}
			else if (c == 0x3)
			{
				cputs( "\nControl-C detected. Exiting input mode...\n");
				gotoxy(0, wherey()+1);
				break;
			}
			else
				cputc(c);
		}
		
	}
	
	
	//	setMappedRedbusDevice(3);
	//
	//	{
	//		unsigned char i = 0;
	//	while (1)
	//	{
	//		POKE( 0x302, i ); //reset iox
	//		i = !i;
	//	}
	//	}
	
	cputs( "Program finished\n");

	return 0;
}
