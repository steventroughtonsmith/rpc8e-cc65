; -----------------------------------------------------------------------------
; mmu.s
;
; MMU opcode wrappers for cc65-rpc8e
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

; FIXME: Should include conditionals here so that the code will run on 65816
;	machines with the RPC8 memory map, but are lacking the custom opcodes and
;	MMU.  Could implement the same functionality in software, placing
;	procedures in a segment > 64k and call them instead of emitting the
;	custom opcodes.  This would be useful if anyone ever builds a real RPC8.
;	>_>
;

; FIXME: Getting 16-bit values out of the MMU is a bit tricky. In the default
;   mode for an rpc8e program, flag M == 1, which means A is 8 bits wide. This
;   can't be changed reliably since cc65 support libraries rely on A being 8
;   bits. The emulator (and presumably the real thing, haven't tested it yet)
;   will happily write MMU values to A, but by default you can only read the
;   bottom byte. Fortunately the top byte seems to be preserved (as is the
;   default for real '816s), but A/B need to be exchanged to read both. This
;   problem also applies to arguments (writing to MMU). There are two solutions:
;
;   1) Exec "xba" before returning. The returned type is the same, but now
;   address values will be pages instead of full addresses, so e.g. the RedBus
;   window would need to be page-aligned. If it's only ever set with these
;   funcs, this shouldn't be a problem since the window is page-sized anyway.
;   Callers will have to shift the result left to get the effective address.
;
;   2) Return AX (or however cc65 returns 16-bit values). This requires changing
;   the return type to 16-bit, but full address values would be returned. This
;   would probably be the best solution for setting/getting the brk/por
;   addresses.
;
;   As of this writing (Jan 2013), the return values are uchar, as are the
;   arguments, so it's assumed that page values are to be taken/returned anyway.
;   Changing these functions later shouldn't be an issue.
;   -- ccfreak2k

.export _setMappedRedbusDevice, _getMappedRedbusDevice, _setRedbusWindowOffset, _getRedbusWindowOffset
.export _enableRedbus, _disableRedbus, _setMemoryMappedWindow, _getMemoryMappedWindow
.export _enableExternalMemoryMappedWindow, _disableExternalMemoryMappedWindow, _setBrkAddress, _getBrkAddress
.export _setPorAddress, _getPorAddress, _logRegisterA

.segment "CODE"

; Set the redbus device that we wish to communicate with
.proc _setMappedRedbusDevice: near
	.byte $EF
	.byte $00
	rts
.endproc

; Get the current device being communicated with
.proc _getMappedRedbusDevice: near
	.byte $EF
	.byte $80
	rts
.endproc

; Set the address in memory for the redbus window
; NOTE: Currently the value is page-aligned.
.proc _setRedbusWindowOffset: near
	xba
	and #$00
	.byte $EF
	.byte $01
	rts
.endproc

; Get the address in memory for the redbus window
; NOTE: Currently the value is page-aligned.
.proc _getRedbusWindowOffset: near
	.byte $EF
	.byte $81
	and #$00
	xba
	rts
.endproc

; Enable the redbus window
.proc _enableRedbus: near
	.byte $EF
	.byte $02
	rts
.endproc

; Disable the redbus window
.proc _disableRedbus: near
	.byte $EF
	.byte $82
	rts
.endproc

; Set external memory mapped window
; NOTE: Currently the value is page-aligned.
.proc _setMemoryMappedWindow: near
	xba
	and #$00
	.byte $EF
	.byte $03
	rts
.endproc

; Get external memory mapped window
; NOTE: Currently the value is page-aligned.
.proc _getMemoryMappedWindow: near
	.byte $EF
	.byte $83
	and #$00
	xba
	rts
.endproc

; Enable the external memory-mapped window
.proc _enableExternalMemoryMappedWindow: near
	.byte $EF
	.byte $04
	rts
.endproc

; Disable the external memory-mapped window
.proc _disableExternalMemoryMappedWindow: near
	.byte $EF
	.byte $84
	rts
.endproc

.proc _setBrkAddress: near
	xba
	and #$00
	.byte $EF
	.byte $05
	rts
.endproc

; Get current BRK address
; NOTE: Page-aligned for now
.proc _getBrkAddress: near
	.byte $EF
	.byte $85
	and #$00
	xba
	rts
.endproc

; Set POR (power-on-reset) address
; NOTE: Page-aligned for now
.proc _setPorAddress: near
	xba
	and #$00
	.byte $EF
	.byte $06
	rts
.endproc

; Get current POR address
; NOTE: Page-aligned for now
.proc _getPorAddress: near
	.byte $EF
	.byte $86
	and #$00
	xba
	rts
.endproc

; Write Accumulator to log
.proc _logRegisterA: near
	.byte $EF
	.byte $FF
	rts
.endproc


