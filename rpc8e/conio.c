// -----------------------------------------------------------------------------
// conio.c
//
// Conio functions for cc65-rpc8e
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
#include <peekpoke.h>

void blit(unsigned char x, unsigned char y, unsigned char width, unsigned char height);

// FIXME: Move the direct hw manipulation stuff to screen.c and call
//	those funcs from here....

unsigned char __conio_reverseVideo = 0;

extern void bzero(void *, unsigned char);

extern unsigned char getMappedRedbusDevice();
extern void setMappedRedbusDevice(unsigned char);


void blit_shift(unsigned char sx, unsigned char sy, unsigned char dx, unsigned char dy, unsigned char width, unsigned char height)
{
	// FIXME: Call MMU to the make sure screen is the enabled device......

	POKE( 0x30a, dx);
	POKE( 0x30b, dy);
	
	POKE( 0x308, sx );
	POKE( 0x309, sy );

	POKE( 0x30c, width );
	POKE( 0x30d, height );

	POKE( 0x307, 3 );		// blitter SHIFT command
	while ( PEEK( 0x307 ) == 3 )
	{
		// WAI
	}
	
}

void blit_fill(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char fillchar)
{
	// FIXME: Call MMU to the make sure screen is the enabled device......
	
	POKE( 0x308, fillchar);
	POKE( 0x30a, x);
	POKE( 0x30b, y);
	
	POKE( 0x30c, width );
	POKE( 0x30d, height );
	
	POKE( 0x307, 1);			// blitter FILL command
	while ( PEEK( 0x307 ) == 1)
	{
		// WAI
	}

	// reset blit size to 0
	
	POKE( 0x300, 0 ); // set row to 0
	POKE( 0x301, 0 );
	POKE( 0x302, 0 );
	
}

/* Clear the whole screen and put the cursor into the top left corner */
void clrscr()
{
	blit_fill(0,0,80,50,0x20);
	gotoxy(0,0);
}

/* Return true if there's a key waiting, return false if not */
unsigned char kbhit(void) {
    return PEEK(0x304) != PEEK(0x305);
}

/* Set the cursor to the specified X position, leave the Y position untouched */
void __fastcall__ gotox( unsigned char x ) // __fastcall__
{
	// FIXME: Call MMU to the make sure screen is the enabled device......
	POKE( 0x301, x );
}

/* Set the cursor to the specified Y position, leave the X position untouched */
void __fastcall__ gotoy( unsigned char y )
{
	// FIXME: Call MMU to the make sure screen is the enabled device......
	POKE( 0x300, y );	// also set row
	POKE( 0x302, y );
}

/* Set the cursor to the specified position */
void __fastcall__ gotoxy( unsigned char x, unsigned char y ) //
{
	// FIXME: Call MMU to the make sure screen is the enabled device......
	POKE( 0x300, y );	// also set row
	POKE( 0x301, x );
	POKE( 0x302, y );
}

/* Return the X position of the cursor */
unsigned char wherex( void )
{
	// FIXME: Call MMU to the make sure screen is the enabled device......
	return PEEK( 0x301 );
}

/* Return the Y position of the cursor */
unsigned char wherey( void )
{
	// FIXME: Call MMU to the make sure screen is the enabled device......
	return PEEK( 0x302 );
}

/* Output one character at the current cursor position */
void __fastcall__ cputc( char c )
{
	unsigned char x;
	unsigned char y;
	unsigned char i;
	
	// FIXME: Call MMU to the make sure screen is the enabled device......
	
	// Set or unset reverse video bit, if needed.
	if( __conio_reverseVideo )
		c += 128;
	
	// Read the current cursor position.
	x = PEEK( 0x301 );
	y = PEEK( 0x302 );
	
	// Set the display memory window to the line the cursor is on.
	POKE( 0x300, y );

	// Write the character the the column the cursor is in, within the display
	//	memory window.
	if ( c != '\n')
		POKE( 0x310+x, c );
	
	// Advance the cursor, moving to the next line and scrolling the screen
	//	if needed.
	++x;
	if( x > 79 || c == '\n' )
	{
		x = 0;
		if( y >= 49 )
		{
			// Scroll...
			blit_shift(0,1,0,0,80,49);

			for (i = 0; i<80; i++)
				POKE( 0x310 + i, 0x20 );
				
		}
		else
		{	// no need to set if Y was 49. 
			++y;
			POKE( 0x302, y );
			POKE( 0x300, y );	// set row too
		}
	}
	
	// Set the cursor to the new position.
	POKE( 0x301, x );
}

/* Same as "gotoxy (x, y); cputc (c);" */
void __fastcall__ cputcxy( unsigned char x, unsigned char y, char c )
{
	gotoxy( x, y );
	cputc( c );
}


/* Output a NUL-terminated string at the current cursor position */
void __fastcall__ cputs( const char* s )
{

	while( *(unsigned char *)(s) != 0 )
	{
		cputc( *(unsigned char *)s++ );
	}
	
}

/* Same as "gotoxy (x, y); puts (s);" */
void __fastcall__ cputsxy( unsigned char x, unsigned char y, const char* s )
{
	gotoxy( x, y );
	cputs( s );
}

/* Like printf(), but uses direct screen output */
//int cprintf( const char* format, ... )
//{
//	// FIXME: Stub.
//	return 0;
//}

/* Like vprintf(), but uses direct screen output */
//int __fastcall__ vcprintf( const char* format, va_list ap )
//{
//	va_list ap = __AX__;
//	// FIXME: Stub.
//	return 0;
//}

/* Return a character from the keyboard. If there is no character available,
 * the function waits until the user does press a key. If cursor is set to
 * 1 (see below), a blinking cursor is displayed while waiting.
 */
char cgetc( void )
{
        unsigned char key;
	unsigned char pos;

	while (!kbhit())
	{
		// WAI
	}

	key = PEEK(0x306);
	pos = PEEK(0x304)+1;
	if (pos > 0x10)
		pos = 0;
	POKE(0x304,pos);
	
	return key;
}

/* Like scanf(), but uses direct keyboard input */
//int cscanf( const char* format, ... )
//{
//	// FIXME: Stub.
//	return 0;
//}

/* Like vscanf(), but uses direct keyboard input */
//int __fastcall__ vcscanf( const char* format, va_list ap )
//{
//	// FIXME: Stub.
//	return 0;
//}

/* If onoff is 1, a cursor is displayed when waiting for keyboard input. If
 * onoff is 0, the cursor is hidden when waiting for keyboard input. The
 * function returns the old cursor setting.
 */
unsigned char __fastcall__ cursor( unsigned char onoff )
{
	// FIXME: Call MMU to the make sure screen is the enabled device......
	unsigned char oldStatus = PEEK( 0x303 );
	if( onoff )
		POKE( 0x303, 2 );
	else
		POKE( 0x303, 0 );
	return oldStatus;
}

/* Enable/disable reverse character display. This may not be supported by
 * the output device. Return the old setting.
 */
unsigned char __fastcall__ revers( unsigned char onoff )
{
	unsigned char oldStatus = __conio_reverseVideo;
	__conio_reverseVideo = onoff;
	return oldStatus;
}

/* Set the color for text output. The old color setting is returned. */
//unsigned char __fastcall__ textcolor( unsigned char color )
//{
//	// FIXME: Stub.
//	return 0;
//}

/* Set the color for the background. The old color setting is returned. */
//unsigned char __fastcall__ bgcolor( unsigned char color )
//{
//	// FIXME: Stub.
//	return 0;
//}

/* Set the color for the border. The old color setting is returned. */
//unsigned char __fastcall__ bordercolor( unsigned char color )
//{
//	// FIXME: Stub.
//	return 0;
//}

/* Output a horizontal line with the given length starting at the current
 * cursor position.
 */
void __fastcall__ chline( unsigned char length )
{
	while( length )
	{
		cputc( 0 );
		--length;
	}
}

/* Same as "gotoxy (x, y); chline (length);" */
void __fastcall__ chlinexy( unsigned char x, unsigned char y, unsigned char length )
{
	gotoxy( x, y );
	chline( length );
}

/* Output a vertical line with the given length at the current cursor
 * position.
 */
void __fastcall__ cvline( unsigned char length )
{
	// FIXME: Optimize me.
	unsigned char x = wherex();
	unsigned char y = wherey();
	unsigned char i;
	for( i=0; i<length; i++ )
	{
		gotoxy( x, y+i );
		cputc( 1 );
	}
}

/* Same as "gotoxy (x, y); cvline (length);" */
void __fastcall__ cvlinexy( unsigned char x, unsigned char y, unsigned char length )
{
	gotoxy( x, y );
	cvline( length );
}

/* Clear part of a line (write length spaces). */
void __fastcall__ cclear( unsigned char length )
{
	while( length )
	{
		cputc( ' ' );
		--length;
	}
}

/* Same as "gotoxy (x, y); cclear (length);" */
void __fastcall__ cclearxy( unsigned char x, unsigned char y, unsigned char length )
{
	gotoxy( x, y );
	cclear( length );
}

/* Return the current screen size. */
void __fastcall__ screensize( unsigned char* x, unsigned char* y )
{
	*x = 80;
	*y = 50;
}

//void __fastcall__ cputhex8( unsigned char val )
//{
//	// FIXME: Stub.
//}

//void __fastcall__ cputhex16( unsigned val )
//{
//	// FIXME: Stub.
//}
