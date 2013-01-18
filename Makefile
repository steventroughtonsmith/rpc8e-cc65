.PHONY:	all
all: library

.PHONY:	library
library:
	make -C upstream
	make -C rpc8e
	rm -f rpc8e.lib
	ar65 a rpc8e.lib rpc8e/*.o upstream/common/*.o upstream/runtime/*.o

.PHONY:	package
package: library padimage
	tar --transform "s,^,cc65-rpc8_$$(git rev-list --max-count=1 HEAD)/,S" -cjf cc65-rpc8_$$(git rev-list --max-count=1 HEAD).tar.bz2 padimage.c padimage rpc8e.cfg rpc8e.lib

.PHONY: padimage
padimage:
	gcc -O -o padimage util/padimage.c

.PHONY: test
test: all padimage
	cl65 --cpu 65816 -Osir -g -T -t none -c -o test.o test/test.c
	ld65 -o test.img --define __STACKSIZE__="$$200" -C rpc8e.cfg -m test.map  test.o rpc8e.lib
	rm test.o
	./padimage test.img

.PHONY: testsuite
testsuite: test
	cl65 --cpu 65816 -Osir -g -T -t none -c -o test_iobus.o test/test_iobus.c
	ld65 -o test_iobus.img --define __STACKSIZE__="$$200" -C rpc8e.cfg -m test_iobus.map  test_iobus.o rpc8e.lib
	rm test_iobus.o
	./padimage test_iobus.img
	cl65 --cpu 65816 -Osir -g -T -t none -c -o test_dio.o test/test_dio.c
	ld65 -o test_dio.img --define __STACKSIZE__="$$200" -C rpc8e.cfg -m test_dio.map  test_dio.o rpc8e.lib
	rm test_dio.o
	./padimage test_dio.img

.PHONY: clean
clean:
	make -C rpc8e clean
	make -C upstream clean
	rm test.map test.img || true

.PHONY: distclean
distclean:
	make clean
	make -C upstream distclean
	rm rpc8e.lib padimage cc65-rpc8_*.tar.bz2 || true
	
.PHONY: getupstream
getupstream:
	make -C upstream getupstream
	