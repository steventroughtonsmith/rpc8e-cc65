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
	.dbg		file, "locale.c", 1634, 1065131096
	.dbg		file, "/Users/steven/bin/lib/cc65/include/locale.h", 3420, 1344797532
	.dbg		file, "/Users/steven/bin/lib/cc65/include/limits.h", 2978, 1344797532
	.export		_localeconv
	.export		_setlocale

.segment	"DATA"

_EmptyString:
	.byte	$00
_lc:
	.addr	_EmptyString
	.addr	L0003
	.addr	_EmptyString
	.addr	_EmptyString
	.addr	_EmptyString
	.addr	_EmptyString
	.addr	_EmptyString
	.addr	_EmptyString
	.addr	_EmptyString
	.addr	_EmptyString
	.byte	$FF
	.byte	$FF
	.byte	$FF
	.byte	$FF
	.byte	$FF
	.byte	$FF
	.byte	$FF
	.byte	$FF

.segment	"RODATA"

L0003:
	.byte	$2E,$00
L0022:
	.byte	$43,$00

; ---------------------------------------------------------------
; __near__ struct lconv* __near__ localeconv (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_localeconv: near

	.dbg	func, "localeconv", "00", extern, "_localeconv"

.segment	"CODE"

;
; return &lc;
;
	.dbg	line, "locale.c", 54
	lda     #<(_lc)
	ldx     #>(_lc)
;
; }
;
	.dbg	line, "locale.c", 55
	rts
	.dbg	line

.endproc

; ---------------------------------------------------------------
; __near__ unsigned char* __near__ __fastcall__ setlocale (int, __near__ const unsigned char*)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_setlocale: near

	.dbg	func, "setlocale", "00", extern, "_setlocale"
	.dbg	sym, "$anon-param-0001", "00", auto, 2
	.dbg	sym, "locale", "00", auto, 0

.segment	"CODE"

;
; {
;
	.dbg	line, "locale.c", 60
	jsr     pushax
;
; if (locale == 0 || (locale [0] == 'C' && locale [1] == '\0') || locale [0] == '\0') {
;
	.dbg	line, "locale.c", 61
	lda     (sp)
	ldy     #$01
	ora     (sp),y
	beq     L002A
	lda     (sp),y
	sta     ptr1+1
	lda     (sp)
	sta     ptr1
	lda     (ptr1)
	cmp     #$43
	bne     L0026
	ldy     #$01
	lda     (sp),y
	sta     ptr1+1
	lda     (sp)
	sta     ptr1
	ldy     #$01
	lda     (ptr1),y
	beq     L002A
	bra     L002C
L0026:	ldy     #$01
L002C:	lda     (sp),y
	sta     ptr1+1
	lda     (sp)
	sta     ptr1
	lda     (ptr1)
	beq     L002A
	ldx     #$00
	txa
	jmp     incsp4
;
; return "C";
;
	.dbg	line, "locale.c", 63
L002A:	lda     #<(L0022)
	ldx     #>(L0022)
	jmp     incsp4
	.dbg	line

.endproc
