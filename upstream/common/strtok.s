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
	.dbg		file, "strtok.c", 1493, 1116364269
	.dbg		file, "/Users/steven/bin/lib/cc65/include/string.h", 4883, 1344797532
	.dbg		file, "/Users/steven/bin/lib/cc65/include/stddef.h", 2972, 1344797532
	.dbg		sym, "strchr", "00", extern, "_strchr"
	.import		_strchr
	.export		_strtok

.segment	"DATA"

_Last:
	.word	$0000

; ---------------------------------------------------------------
; __near__ unsigned char* __near__ __fastcall__ strtok (register __near__ unsigned char*, __near__ const unsigned char*)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_strtok: near

	.dbg	func, "strtok", "00", extern, "_strtok"
	.dbg	sym, "s1", "00", register, "regbank", 4
	.dbg	sym, "s2", "00", auto, 0
	.dbg	sym, "c", "00", auto, -1
	.dbg	sym, "start", "00", auto, -3

.segment	"CODE"

;
; {
;
	.dbg	line, "strtok.c", 31
	jsr     pushax
	ldy     #$02
	ldx     #$04
	jsr     regswap2
;
; if (s1 == 0) {
;
	.dbg	line, "strtok.c", 36
	jsr     decsp3
	lda     regbank+4
	ora     regbank+4+1
	bne     L0003
;
; s1 = Last;
;
	.dbg	line, "strtok.c", 37
	lda     _Last
	sta     regbank+4
	lda     _Last+1
	sta     regbank+4+1
;
; if (*s1 == '\0') {
;
	.dbg	line, "strtok.c", 41
L0003:	lda     (regbank+4)
	bne     L003A
;
; return 0;
;
	.dbg	line, "strtok.c", 42
	tax
	jmp     L0002
;
; ++s1;
;
	.dbg	line, "strtok.c", 49
L000B:	inc     regbank+4
	bne     L003A
	inc     regbank+4+1
;
; while ((c = *s1) && strchr (s2, c) != 0) {
;
	.dbg	line, "strtok.c", 48
L003A:	lda     (regbank+4)
	ldy     #$02
	sta     (sp),y
	tax
	beq     L0040
	ldy     #$06
	jsr     pushwysp
	ldy     #$04
	lda     (sp),y
	ldx     #$00
	jsr     _strchr
	cpx     #$00
	bne     L000B
	cmp     #$00
	bne     L000B
;
; if (c == '\0') {
;
	.dbg	line, "strtok.c", 51
	ldy     #$02
L0040:	lda     (sp),y
	bne     L0018
;
; Last = s1;
;
	.dbg	line, "strtok.c", 53
	lda     regbank+4
	sta     _Last
	lda     regbank+4+1
	sta     _Last+1
;
; return 0;
;
	.dbg	line, "strtok.c", 54
	txa
	bra     L0002
;
; start = s1;
;
	.dbg	line, "strtok.c", 58
L0018:	lda     regbank+4
	ldx     regbank+4+1
	jsr     stax0sp
;
; while ((c = *s1) && strchr (s2, c) == 0) {
;
	.dbg	line, "strtok.c", 61
	bra     L0021
;
; ++s1;
;
	.dbg	line, "strtok.c", 62
L001F:	inc     regbank+4
	bne     L0021
	inc     regbank+4+1
;
; while ((c = *s1) && strchr (s2, c) == 0) {
;
	.dbg	line, "strtok.c", 61
L0021:	lda     (regbank+4)
	ldy     #$02
	sta     (sp),y
	tax
	beq     L0041
	ldy     #$06
	jsr     pushwysp
	ldy     #$04
	lda     (sp),y
	ldx     #$00
	jsr     _strchr
	cpx     #$00
	bne     L0038
	cmp     #$00
	beq     L001F
;
; if (c == '\0') {
;
	.dbg	line, "strtok.c", 64
L0038:	ldy     #$02
L0041:	lda     (sp),y
	bne     L002C
;
; Last = s1;
;
	.dbg	line, "strtok.c", 66
	lda     regbank+4
	sta     _Last
	lda     regbank+4+1
	sta     _Last+1
;
; } else {
;
	.dbg	line, "strtok.c", 67
	bra     L0030
;
; *s1 = '\0';
;
	.dbg	line, "strtok.c", 68
L002C:	lda     #$00
	sta     (regbank+4)
;
; Last = s1 + 1;
;
	.dbg	line, "strtok.c", 69
	lda     regbank+4
	ldx     regbank+4+1
	ina
	bne     L0035
	inx
L0035:	sta     _Last
	stx     _Last+1
;
; return start;
;
	.dbg	line, "strtok.c", 73
L0030:	dey
	lda     (sp),y
	tax
	lda     (sp)
;
; }
;
	.dbg	line, "strtok.c", 74
L0002:	pha
	ldy     #$05
	lda     (sp),y
	sta     regbank+4
	iny
	lda     (sp),y
	sta     regbank+5
	pla
	jmp     incsp7
	.dbg	line

.endproc
