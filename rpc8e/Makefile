#
# cc65 makefile for the rpc8e specific modules
#

.SUFFIXES: .o .s .c

AS	= ca65 -I ~/bin/lib/cc65/asminc
CC	= cc65 -I ~/bin/lib/cc65/include
LD	= ld65

AFLAGS	= --cpu 65816 --verbose -t none
CFLAGS	= --cpu 65816 -Osir -g -T -t none

%.o:   	%.c
	@$(CC) $(CFLAGS) $<
	@$(AS) -o $@ $(AFLAGS) $(*).s

%.o:	%.s
	@$(AS) -g -o $@ $(AFLAGS) $<

C_OBJS =		conio.o			\
				write.o			\
				io.o

S_OBJS  =       crt0.o          \
                ctype.o			\
				mmu.o

.PHONY:	all clean distclean

all:   	$(C_OBJS) $(S_OBJS)

clean:
	$(RM) $(C_OBJS:.o=.s) $(C_OBJS) $(S_OBJS)

distclean:
	$(RM) $(C_OBJS:.o=.s) $(C_OBJS) $(S_OBJS)
