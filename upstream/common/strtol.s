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
	.dbg		file, "strtol.c", 2969, 1253048168
	.dbg		file, "/Users/steven/bin/lib/cc65/include/limits.h", 2978, 1344797532
	.dbg		file, "/Users/steven/bin/lib/cc65/include/ctype.h", 7921, 1344797532
	.dbg		file, "/Users/steven/bin/lib/cc65/include/errno.h", 4695, 1344797532
	.dbg		file, "/Users/steven/bin/lib/cc65/include/stdlib.h", 5606, 1344797532
	.dbg		sym, "_ctype", "00", extern, "__ctype"
	.dbg		sym, "_errno", "00", extern, "__errno"
	.import		__ctype
	.import		__errno
	.export		_strtol

; ---------------------------------------------------------------
; long __near__ __fastcall__ strtol (__near__ const unsigned char*, __near__ __near__ unsigned char**, int)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_strtol: near

	.dbg	func, "strtol", "00", extern, "_strtol"
	.dbg	sym, "nptr", "00", auto, 4
	.dbg	sym, "endptr", "00", auto, 2
	.dbg	sym, "base", "00", auto, 0
	.dbg	sym, "S", "00", register, "regbank", 4
	.dbg	sym, "Val", "00", auto, -6
	.dbg	sym, "Minus", "00", auto, -7
	.dbg	sym, "Ovf", "00", auto, -8
	.dbg	sym, "CvtCount", "00", auto, -10
	.dbg	sym, "DigitVal", "00", auto, -11
	.dbg	sym, "MaxVal", "00", auto, -15
	.dbg	sym, "MaxDigit", "00", auto, -16

.segment	"CODE"

;
; {
;
	.dbg	line, "strtol.c", 10
	jsr     pushax
;
; register const char* S          = nptr;
;
	.dbg	line, "strtol.c", 11
	lda     regbank+4
	ldx     regbank+5
	jsr     pushax
	ldy     #$07
	lda     (sp),y
	sta     regbank+4+1
	dey
	lda     (sp),y
	sta     regbank+4
;
; unsigned long        Val        = 0;
;
	.dbg	line, "strtol.c", 12
	jsr     pushl0
;
; unsigned char        Minus      = 0;
;
	.dbg	line, "strtol.c", 13
	jsr     pusha
;
; unsigned char        Ovf        = 0;
;
	.dbg	line, "strtol.c", 14
	jsr     pusha
;
; unsigned             CvtCount   = 0;
;
	.dbg	line, "strtol.c", 15
	jsr     push0
;
; while (isspace (*S)) {
;
	.dbg	line, "strtol.c", 22
	jsr     decsp6
	bra     L000A
;
; ++S;
;
	.dbg	line, "strtol.c", 23
L0008:	inc     regbank+4
	bne     L000A
	inc     regbank+4+1
;
; while (isspace (*S)) {
;
	.dbg	line, "strtol.c", 22
L000A:	lda     (regbank+4)
	tay
	lda     __ctype,y
	and     #$60
	bne     L0008
;
; switch (*S) {
;
	.dbg	line, "strtol.c", 27
	lda     (regbank+4)
;
; }
;
	.dbg	line, "strtol.c", 33
	cmp     #$2B
	beq     L0022
	cmp     #$2D
	bne     L001C
;
; Minus = 1;
;
	.dbg	line, "strtol.c", 29
	lda     #$01
	ldy     #$09
	sta     (sp),y
;
; ++S;
;
	.dbg	line, "strtol.c", 32
L0022:	inc     regbank+4
	bne     L001C
	inc     regbank+4+1
;
; if (base == 0) {
;
	.dbg	line, "strtol.c", 38
L001C:	ldy     #$10
	lda     (sp),y
	iny
	ora     (sp),y
	bne     L00BE
;
; if (*S == '0') {
;
	.dbg	line, "strtol.c", 39
	lda     (regbank+4)
	cmp     #$30
	bne     L00BD
;
; ++S;
;
	.dbg	line, "strtol.c", 40
	inc     regbank+4
	bne     L002B
	inc     regbank+4+1
;
; if (*S == 'x' || *S == 'X') {
;
	.dbg	line, "strtol.c", 41
L002B:	lda     (regbank+4)
	cmp     #$78
	beq     L00BB
	cmp     #$58
	bne     L00BC
;
; ++S;
;
	.dbg	line, "strtol.c", 42
L00BB:	inc     regbank+4
	bne     L0030
	inc     regbank+4+1
;
; base = 16;
;
	.dbg	line, "strtol.c", 43
L0030:	dey
	tya
;
; } else {
;
	.dbg	line, "strtol.c", 44
	bra     L00D6
;
; base = 8;
;
	.dbg	line, "strtol.c", 45
L00BC:	dey
	lda     #$08
	sta     (sp),y
	lda     #$00
	iny
	sta     (sp),y
;
; } else {
;
	.dbg	line, "strtol.c", 47
	bra     L003A
;
; base = 10;
;
	.dbg	line, "strtol.c", 48
L00BD:	dey
	lda     #$0A
L00D6:	sta     (sp),y
	lda     #$00
	iny
	sta     (sp),y
;
; } else if (base == 16 && *S == '0' && (S[1] == 'x' || S[1] == 'X')) {
;
	.dbg	line, "strtol.c", 50
	bra     L003A
L00BE:	lda     (sp),y
	bne     L003A
	dey
	lda     (sp),y
	cmp     #$10
	bne     L003A
	lda     (regbank+4)
	cmp     #$30
	bne     L003A
	ldy     #$01
	lda     (regbank+4),y
	cmp     #$78
	beq     L00C3
	cmp     #$58
	bne     L003A
;
; S += 2;
;
	.dbg	line, "strtol.c", 51
L00C3:	lda     #$02
	clc
	adc     regbank+4
	sta     regbank+4
	bcc     L003A
	inc     regbank+4+1
;
; if (Minus) {
;
	.dbg	line, "strtol.c", 57
L003A:	ldy     #$09
	lda     (sp),y
	beq     L0046
;
; MaxVal = LONG_MIN;
;
	.dbg	line, "strtol.c", 58
	ldy     #$01
	lda     #$00
	sta     (sp),y
	iny
	sta     (sp),y
	iny
	sta     (sp),y
	lda     #$80
;
; } else {
;
	.dbg	line, "strtol.c", 59
	bra     L00D0
;
; MaxVal = LONG_MAX;
;
	.dbg	line, "strtol.c", 60
L0046:	ldy     #$01
	dea
	sta     (sp),y
	iny
	sta     (sp),y
	iny
	sta     (sp),y
	lda     #$7F
L00D0:	iny
	sta     (sp),y
;
; MaxDigit = MaxVal % base;
;
	.dbg	line, "strtol.c", 62
	jsr     ldeaxysp
	jsr     pusheax
	ldy     #$15
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	jsr     axlong
	jsr     tosumodeax
	sta     (sp)
;
; MaxVal  /= base;
;
	.dbg	line, "strtol.c", 63
	ldy     #$04
	jsr     ldeaxysp
	jsr     pusheax
	ldy     #$15
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	jsr     axlong
	jsr     tosudiveax
	ldy     #$01
	jsr     steaxysp
;
; if (isdigit (*S)) {
;
	.dbg	line, "strtol.c", 69
L0052:	lda     (regbank+4)
	tay
	lda     __ctype,y
	and     #$04
	beq     L0056
;
; DigitVal = *S - '0';
;
	.dbg	line, "strtol.c", 70
	ldx     #$00
	lda     (regbank+4)
	sec
	sbc     #$30
;
; } else if (isupper (*S)) {
;
	.dbg	line, "strtol.c", 71
	bra     L00D4
L0056:	lda     (regbank+4)
	tay
	lda     __ctype,y
	and     #$02
	beq     L0067
;
; DigitVal = *S - ('A' - 10);
;
	.dbg	line, "strtol.c", 72
	ldx     #$00
	lda     (regbank+4)
	sec
	sbc     #$37
;
; } else if (islower (*S)) {
;
	.dbg	line, "strtol.c", 73
	bra     L00D4
L0067:	lda     (regbank+4)
	tay
	lda     __ctype,y
	and     #$01
	jeq     L0053
;
; DigitVal = *S - ('a' - 10);      
;
	.dbg	line, "strtol.c", 74
	ldx     #$00
	lda     (regbank+4)
	sec
	sbc     #$57
L00D4:	ldy     #$05
	sta     (sp),y
;
; if (DigitVal >= base) {
;
	.dbg	line, "strtol.c", 81
	ldy     #$10
	cmp     (sp),y
	txa
	iny
	sbc     (sp),y
;
; break;
;
	.dbg	line, "strtol.c", 82
	bcs     L0053
;
; if (Val > MaxVal || (Val == MaxVal && DigitVal > MaxDigit)) {
;
	.dbg	line, "strtol.c", 86
	ldy     #$0D
	jsr     ldeaxysp
	jsr     pusheax
	ldy     #$08
	jsr     ldeaxysp
	jsr     tosugteax
	bne     L008E
	ldy     #$0D
	jsr     ldeaxysp
	jsr     pusheax
	ldy     #$08
	jsr     ldeaxysp
	jsr     toseqeax
	beq     L008D
	ldy     #$05
	lda     (sp),y
	sec
	sbc     (sp)
	sta     tmp1
	lda     tmp1
	beq     L008D
	bcc     L008D
;
; Ovf = 1;
;
	.dbg	line, "strtol.c", 87
L008E:	lda     #$01
	ldy     #$08
	sta     (sp),y
;
; if (Ovf == 0) {
;
	.dbg	line, "strtol.c", 91
L008D:	ldy     #$08
	lda     (sp),y
	bne     L0095
;
; Val = (Val * base) + DigitVal;
;
	.dbg	line, "strtol.c", 92
	ldy     #$0D
	jsr     ldeaxysp
	jsr     pusheax
	ldy     #$15
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	jsr     axlong
	jsr     tosumuleax
	jsr     pusheax
	ldy     #$09
	ldx     #$00
	lda     (sp),y
	jsr     tosadd0ax
	ldy     #$0A
	jsr     steaxysp
;
; ++CvtCount;
;
	.dbg	line, "strtol.c", 93
	ldy     #$06
	ldx     #$00
	lda     #$01
	jsr     addeqysp
;
; ++S;
;
	.dbg	line, "strtol.c", 97
L0095:	inc     regbank+4
	jne     L0052
	inc     regbank+4+1
;
; while (1) {
;
	.dbg	line, "strtol.c", 66
	jmp     L0052
;
; if (endptr) {
;
	.dbg	line, "strtol.c", 103
L0053:	ldy     #$13
	lda     (sp),y
	dey
	ora     (sp),y
	beq     L00A5
;
; if (CvtCount > 0) {
;
	.dbg	line, "strtol.c", 104
	ldy     #$06
	lda     (sp),y
	iny
	ora     (sp),y
	beq     L009F
;
; *endptr = (char*) S - 1;
;
	.dbg	line, "strtol.c", 105
	ldy     #$13
	lda     (sp),y
	sta     sreg+1
	dey
	lda     (sp),y
	sta     sreg
	lda     regbank+4
	ldx     regbank+4+1
	sec
	sbc     #$01
	bcs     L00D9
	dex
;
; } else {
;
	.dbg	line, "strtol.c", 106
	bra     L00D9
;
; *endptr = (char*) nptr;
;
	.dbg	line, "strtol.c", 107
L009F:	ldy     #$13
	lda     (sp),y
	sta     sreg+1
	dey
	lda     (sp),y
	sta     sreg
	ldy     #$15
	lda     (sp),y
	tax
	dey
	lda     (sp),y
L00D9:	sta     (sreg)
	ldy     #$01
	txa
	sta     (sreg),y
;
; if (Ovf) {
;
	.dbg	line, "strtol.c", 112
L00A5:	ldy     #$08
	lda     (sp),y
	beq     L00B0
;
; errno = ERANGE;
;
	.dbg	line, "strtol.c", 113
	ldx     #$00
	lda     #$0F
	sta     __errno
	stz     __errno+1
;
; if (Minus) {
;
	.dbg	line, "strtol.c", 114
	iny
	lda     (sp),y
	beq     L00AC
;
; return LONG_MIN;
;
	.dbg	line, "strtol.c", 115
	stz     sreg
	lda     #$80
	sta     sreg+1
	txa
	bra     L00B5
;
; return LONG_MAX;
;
	.dbg	line, "strtol.c", 117
L00AC:	dex
	stx     sreg
	lda     #$7F
	sta     sreg+1
	txa
	bra     L00B5
;
; if (Minus) {
;
	.dbg	line, "strtol.c", 122
L00B0:	iny
	lda     (sp),y
	beq     L00B2
;
; return -(long)Val;
;
	.dbg	line, "strtol.c", 123
	ldy     #$0D
	jsr     ldeaxysp
	jsr     negeax
	bra     L00B5
;
; return Val;
;
	.dbg	line, "strtol.c", 125
L00B2:	ldy     #$0D
	jsr     ldeaxysp
;
; }
;
	.dbg	line, "strtol.c", 127
L00B5:	pha
	ldy     #$0E
	lda     (sp),y
	sta     regbank+4
	iny
	lda     (sp),y
	sta     regbank+5
	pla
	ldy     #$16
	jmp     addysp
	.dbg	line

.endproc
