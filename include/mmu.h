// -----------------------------------------------------------------------------
// mmu.h
//
// MMU header for cc65-rpc8e
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

#ifdef _MMU_H
#define _MMU_H

void __fastcall__ setMappedRedbusDevice( unsigned char deviceId ); // Should this be unsigned short??
unsigned char getMappedRedbusDevice( void ); // Should this be unsigned short??
void __fastcall__ setRedbusWindowOffset( unsigned char offset ); // Should this be void* or unsigned short??
unsigned char getRedbusWindowOffset( void ); // Should this be void* or unsigned short??
void enableRedbus( void )
void disableRedbus( void )
void __fastcall__ setMemoryMappedWindow( unsigned char offset ); // Should this be void* or unsigned short??
unsigned char getMemoryMappedWindow( void ); // Should this be void* or unsigned short??
void __fastcall__ setBrkAddress( void (*fcnAddr)(void) );
void (*getBrkAddress(void))( void );
void __fastcall__ setPorAddress( void (*fcnAddr)(void) );
void (*getPorAddress(void))( void );
void _logRegisterA( void );

#endif // _MMU_H
