; -----------------------------------------------------------------------------
; crt0.s
;
; Startup code for cc65 (RPC8e version)
; -----------------------------------------------------------------------------
;
; Copyright (C) 2012 L. Adamson
;
;  This software is provided 'as-is', without any express or implied
;  warranty.  In no event will the authors be held liable for any damages
;  arising from the use of this software.
;
;  Permission is granted to anyone to use this software for any purpose,
;  including commercial applications, and to alter it and redistribute it
;  freely, subject to the following restrictions:
;
;  1. The origin of this software must not be misrepresented; you must not
;     claim that you wrote the original software. If you use this software
;     in a product, an acknowledgment in the product documentation would be
;     appreciated but is not required.
;  2. Altered source versions must be plainly marked as such, and must not be
;     misrepresented as being the original software.
;  3. This notice may not be removed or altered from any source distribution.
;
;  L. Adamson leaf@dizzydragon.net
;

	.export		_init, _exit
	.import		_main

	.export		__STARTUP__ : absolute = 1	; Mark as startup
	.import		__RAM_START__, __RAM_SIZE__	; Linker generated
	; FIXME: We should probe in _init to determine the actual ram size,
	;	instead of assuming a full 64k...

	.import		copydata, zerobss, initlib, donelib

	.include "zeropage.inc"

.bss

; -----------------------------------------------------------------------------
; Place the startup code in a special segment.

.segment	"STARTUP"


; -----------------------------------------------------------------------------
; A little light 6502 housekeeping.
; FIXME: The boot loader probably already handles this. Do we still need to
;	do this?

_init:
			PHA				; Work around the EL02 SP bug...
			LDX	#$FF		; Initialize stack pointer to $01FF.
			TXS
			CLD				; Clear decimal mode.

; -----------------------------------------------------------------------------
; Set cc65 argument stack pointer.

;			LDA	#<(__RAM_START__ + __RAM_SIZE__)
;			STA	sp
;			LDA	#>(__RAM_START__ + __RAM_SIZE__)
;			STA	sp+1

; -----------------------------------------------------------------------------
; Initialize memory storage.

			JSR	zerobss		; Clear BSS segment.
			JSR	copydata	; Initialize DATA segment.
			JSR	initlib		; Run constructors.


; -----------------------------------------------------------------------------
; Call main().
	
			JSR	_main

; -----------------------------------------------------------------------------
; Cleanup and exit.

_exit:		JSR	donelib		; Run destructors
exitloop:	WAI
			JMP exitloop

xce:
.byte $FB

