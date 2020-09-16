DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS = -O2 -g -ffreestanding -Wall -Wextra
CPPFLAGS = -D__is_kernel
LIBS = -nostdlib -lk -lgcc


OBJS  = $(patsubst %.c,%.o,$(wildcard */*.c))
OBJS +=	$(patsubst %.S,%.o,$(wildcard */*.S))


.PHONY: all clean install install-headers install-kernel

all: test.kernel

test.kernel: $(OBJS) linker.ld
	$(CC) -T linker.ld -o $@ $(CFLAGS) $(OBJS) $(LIBS)
	grub-file --is-x86-multiboot test.kernel
	
%.o: %.c
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

%.o: %.S
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)
	
	

clean:
	rm -f test.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: test.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp test.kernel $(DESTDIR)$(BOOTDIR)
