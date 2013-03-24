// -----------------------------------------------------------------------------
// write.c
//
// write() for cc65-rpc8e
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

int __fastcall__ write ( int fd, const void* buf, unsigned count )
{
    char *cbuf = (char *)buf;
    unsigned char x, y, i, j, linelen;
    
    x = PEEK(0x301);
    y = PEEK(0x302);
    POKE(0x300, y);

    i = 0;
    while (i < count) {
        linelen = count - i;
        linelen = (linelen > (80-x) ? (80-x) : linelen);
        for (j = 0; j < linelen; ++j)
        {
            if (cbuf[i] == '\n')
            {
                x = 80;
                ++i;
                break;
            }
            else
            {
                POKE(0x310 + x, cbuf[i++]);
                POKE(0x301, ++x);
            }
        }

        if (x >= 80)
        {
            if (y >= 49)
            {
                POKE(0x30a, 0);
                POKE(0x30b, 0);
                POKE(0x308, 0);
                POKE(0x309, 1);
                POKE(0x30c, 80);
                POKE(0x30d, 49);
                POKE(0x307, 3);
                while (PEEK(0x307) == 3);

                for (j = 0; j < 80; ++j)
                    POKE(0x310 + j, 0x20);
            }
            else
            {
                POKE(0x302, ++y);
                POKE(0x300, y);
            }
            
            x = 0;
            POKE(0x301, x);
        }
    }

    return count;
}

int __fastcall__ write_old ( int fd, const void* buf, unsigned count )
{
    unsigned i = 0;
	char *cbuf = (char *) buf;

    while (i < count) {
        cputc(cbuf[i]);
        i = i + 1;
    }

    return count;
}
