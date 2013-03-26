ifdef SystemRoot
	RM = del /Q
	fixpath = $(subst /,\,$1) 
else
	RM = rm -f
	fixpath = $(subst \,/.$1)
endif
export RM

CC = cl65
CFLAGS = --cpu 65816 -Osir -g -T -t none -c -Iinclude

AS = ca65
AFLAGS = --cpu 65816 --verbose -t none -g

TEST_OBJ_DIR = test
TEST_SRC_DIR = test
RP_CFG = rpc8e.cfg
RP_MAP = test.map
RP_LIB = rpc8e.lib

RP_OBJ_DIR = rpc8e
RP_SRC_DIR = rpc8e

RP_OBJS = \
	conio.o \
	dio.o \
	write.o \
	io.o \
	crt0.o \
	ctype.o \
	mmu.o \
	oserror.o

TEST_IMGS = \
	test_printf.img \
	test_loop.img \
	test_assert.img \
	test_ctype.img \
	test_dio.img \
	test_errno.img \
	test_limits.img \
	test_locale.img \
	test_setjmp.img \
	test_signal.img \
	test_stdarg.img \
	test_stddef.img

PADIMAGE_OBJS = \
	padimage.o

.PHONY:	all
all: upstream rpc8e.lib

.PHONY: upstream
upstream:
	$(MAKE) -C upstream

rpc8e.lib: $(RP_OBJS:%.o=$(RP_OBJ_DIR)/%.o)
	$(RM) $@
	ar65 a $@ $^ upstream/common/*.o upstream/runtime/*.o

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.s
	$(AS) $(AFLAGS) -o $@ $^

.PHONY:	package
package: library padimage
	tar --transform "s,^,cc65-rpc8_$$(svn info | grep Revision | cut -d\  -f2)/,S" -cjf cc65-rpc8_$$(svn info | grep Revision | cut -d\  -f2).tar.bz2 padimage.c padimage rpc8e.cfg rpc8e.lib

padimage: util/padimage.c
	gcc -O -o $@ $^

.PHONY: test
test: all padimage $(TEST_IMGS)

%.img: $(TEST_OBJ_DIR)/%.o
	ld65 -o $@ --define __STACKSIZE__="$200" -C $(RP_CFG) -m $(RP_MAP) $^ $(RP_LIB)
	./padimage $@

.PHONY: clean
clean:
	make -C upstream clean
	$(RM) test.map $(TEST_IMGS) rpc8e.lib padimage
	$(RM) $(call fixpath, $(RP_OBJS:%.o=$(RP_OBJ_DIR)/%.o))

.PHONY: distclean
distclean: clean
	make -C upstream distclean
	$(RM) rpc8e.lib padimage cc65-rpc8_*.tar.bz2 || true
	
.PHONY: getupstream
getupstream:
	make -C upstream getupstream
	
