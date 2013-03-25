ifdef SystemRoot
	RM = del /Q
else
	RM = rm -f
endif
export RM

OBJ_DIR = test
SRC_DIR = test
RP_CFG = rpc8e.cfg
RP_MAP = test.map
RP_LIB = rpc8e.lib

TEST_IMGS = \
	test_printf.img \
	test_loop.img \
	test_assert.img \
	test_ctype.img \
	test_errno.img \
	test_limits.img \
	test_locale.img \
	test_setjmp.img \
	test_signal.img \
	test_stdarg.img \
	test_stddef.img

.PHONY:	all
all: upstream rpc8e.lib

.PHONY: upstream
upstream:
	$(MAKE) -C upstream

rpc8e.lib:
	$(MAKE) -C rpc8e
	$(RM) rpc8e.lib
	ar65 a rpc8e.lib rpc8e/*.o upstream/common/*.o upstream/runtime/*.o

.PHONY:	package
package: library padimage
	tar --transform "s,^,cc65-rpc8_$$(svn info | grep Revision | cut -d\  -f2)/,S" -cjf cc65-rpc8_$$(svn info | grep Revision | cut -d\  -f2).tar.bz2 padimage.c padimage rpc8e.cfg rpc8e.lib

.PHONY: padimage
padimage:
	gcc -O -o padimage util/padimage.c

.PHONY: test
test: all padimage $(TEST_IMGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	cl65 --cpu 65816 -Osir -g -T -t none -c -o $@ $<

%.img: $(OBJ_DIR)/%.o
	ld65 -o $@ --define __STACKSIZE__="$200" -C $(RP_CFG) -m $(RP_MAP) $< $(RP_LIB)
	./padimage $@

.PHONY: clean
clean:
	make -C rpc8e clean
	make -C upstream clean
	$(RM) test.map test.img || true

.PHONY: distclean
distclean:
	make clean
	make -C upstream distclean
	$(RM) rpc8e.lib padimage cc65-rpc8_*.tar.bz2 || true
	
.PHONY: getupstream
getupstream:
	make -C upstream getupstream
	
