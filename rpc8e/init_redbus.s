.include "zeropage.inc"
.include "rp_zeropage.inc"

* = $0500

init
	clc
	xce

	sep #$30	; 8-bit memory, 8-bit regs

	lda $00		; drive
	sta DRIVE_ID

	lda $01		; display
	sta DISPLAY_ID

	mmu #$00	; set display
	mmu #$02	; enable redbus

	lda #$02	; set cursor to blink mode
	sta $0303

	LDX #$2 ;Load 2 to x register



