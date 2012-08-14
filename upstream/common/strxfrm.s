;
; File generated by cc65 v 2.13.9
;
	.fopt		compiler,"cc65 v 2.13.9"
	.setcpu		"65816"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	on
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.dbg		file, "strxfrm.c", 222, 1219867368
	.dbg		file, "/Users/steven/bin/lib/cc65/include/string.h", 4883, 1344797532
	.dbg		file, "/Users/steven/bin/lib/cc65/include/stddef.h", 2972, 1344797532
	.dbg		sym, "strlen", "00", extern, "_strlen"
	.dbg		sym, "strncpy", "00", extern, "_strncpy"
	.import		_strlen
	.import		_strncpy
	.export		_strxfrm

; ---------------------------------------------------------------
; unsigned int __near__ __fastcall__ strxfrm (__near__ unsigned char*, __near__ const unsigned char*, unsigned int)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_strxfrm: near

	.dbg	func, "strxfrm", "00", extern, "_strxfrm"
	.dbg	sym, "dest", "00", auto, 4
	.dbg	sym, "src", "00", auto, 2
	.dbg	sym, "count", "00", auto, 0

.segment	"CODE"

;
; {
;
	.dbg	line, "strxfrm.c", 14
	jsr     pushax
;
; strncpy (dest, src, count);
;
	.dbg	line, "strxfrm.c", 15
	jsr     decsp4
	ldy     #$09
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	ldy     #$02
	sta     (sp),y
	iny
	txa
	sta     (sp),y
	ldy     #$07
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	sta     (sp)
	ldy     #$01
	txa
	sta     (sp),y
	ldy     #$05
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	jsr     _strncpy
;
; return strlen (src);
;
	.dbg	line, "strxfrm.c", 16
	ldy     #$03
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	jsr     _strlen
;
; }
;
	.dbg	line, "strxfrm.c", 17
	jmp     incsp6
	.dbg	line

.endproc
