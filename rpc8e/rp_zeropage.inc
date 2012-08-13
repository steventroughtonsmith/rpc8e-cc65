

Z14		= $02			; 1	; unused
Z15		= Z14 + 1		; 1
MAX_WIDTH	= Z15 + 1		; 1
Z18		= MAX_WIDTH + 1		; 1

DISPLAY_ID	= Z18 + 1		; 1
DRIVE_ID	= DISPLAY_ID + 1	; 1
STATUS		= DRIVE_ID + 1		; 1		free -> $0c
