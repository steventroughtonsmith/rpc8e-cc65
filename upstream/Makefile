AS	= ca65
CC	= cc65
LD	= ld65
AR	= ar65

AFLAGS	= --cpu 65816 -t none
CFLAGS	= --cpu 65816 -Osir -g -T -t none

.PHONY: all
all: common runtime

.PHONY: common
common:
	make -C common AS=$(AS) CC=$(CC) LD=$(LD) AFLAGS="$(AFLAGS)" CFLAGS="$(CFLAGS)"

.PHONY: runtime
runtime:
	make -C runtime AS=$(AS) CC=$(CC) LD=$(LD) AFLAGS="$(AFLAGS)" CFLAGS="$(CFLAGS)"

.PHONY: getupstream
getupstream:
	rm -rf common runtime
	svn export svn://svn.cc65.org/cc65/branches/version-2.13/trunk/libsrc/common
	svn export svn://svn.cc65.org/cc65/branches/version-2.13/trunk/libsrc/runtime
	cd common && rm -rf `find . -type d -name .svn`
	cd runtime && rm -rf `find . -type d -name .svn`
	
.PHONY: clean
clean:
	if -e common; then make -C common zap; fi
	if -e common; then make -C runtime zap; fi
	
.PHONY: distclean
distclean:
	rm -rf common runtime
