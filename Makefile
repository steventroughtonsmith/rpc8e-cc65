ifdef SystemRoot
	RM = del /Q
else
	RM = rm -f
endif
export RM

.PHONY:	all
all: library

.PHONY:	library
library:
	$(MAKE) -C upstream
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
test: all padimage test_loop test_printf

test_loop:
	cl65 --cpu 65816 -Osir -g -T -t none -c -o test_loop.o test/test_loop.c
	ld65 -o test_loop.img --define __STACKSIZE__="$200" -C rpc8e.cfg -m test.map  test_loop.o rpc8e.lib
	$(RM) test_loop.o
	./padimage test_loop.img

test_printf:
	cl65 --cpu 65816 -Osir -g -T -t none -c -o test_printf.o test/test_printf.c
	ld65 -o test_printf.img --define __STACKSIZE__="$200" -C rpc8e.cfg -m test.map  test_printf.o rpc8e.lib
	$(RM) test_printf.o
	./padimage test_printf.img

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
	
