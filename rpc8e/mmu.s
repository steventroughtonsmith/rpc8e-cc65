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

.export _setMappedRedbusDevice, _getMappedRedbusDevice, _setRedbusWindowOffset, _getRedbusWindowOffset
.export _enableRedbus, _disableRedbus, _setMemoryMappedWindow, _getMemoryMappedWindow
.export _setBrkAddress, _getBrkAddress, _setPorAddress, _getPorAddress, _logRegisterA

.segment "CODE"


.proc _setMappedRedbusDevice: near
	.byte $EF
	.byte $00
	rts
.endproc

.proc _getMappedRedbusDevice: near
	.byte $EF
	.byte $80
	rts
.endproc

.proc _setRedbusWindowOffset: near
	.byte $EF
	.byte $01
.endproc

.proc _getRedbusWindowOffset: near
	.byte $EF
	.byte $81
.endproc

.proc _enableRedbus: near

	.byte $EF
	.byte $02
	rts
.endproc

.proc _disableRedbus: near
	.byte $EF
	.byte $82
	rts
.endproc

.proc _setMemoryMappedWindow: near
	.byte $EF
	.byte $03
.endproc

.proc _getMemoryMappedWindow: near
	.byte $EF
	.byte $83
.endproc

.proc _setBrkAddress: near
	.byte $EF
	.byte $05
.endproc

.proc _getBrkAddress: near
	.byte $EF
	.byte $85
.endproc

.proc _setPorAddress: near
	.byte $EF
	.byte $06
.endproc

.proc _getPorAddress: near
	.byte $EF
	.byte $86
.endproc

.proc _logRegisterA: near
	.byte $EF
	.byte $FF
.endproc


