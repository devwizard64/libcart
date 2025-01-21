CART_OBJ := \
	cart/cartinit.o \
	cart/cartexit.o \
	cart/cartcardinit.o \
	cart/cartcardrddram.o \
	cart/cartcardrdcart.o \
	cart/cartcardwrdram.o \
	cart/cartcardwrcart.o

CI_OBJ := \
	ci/ci.o \
	ci/ciinit.o \
	ci/ciexit.o \
	ci/cicardinit.o \
	ci/cicardrddram.o \
	ci/cicardrdcart.o \
	ci/cicardwrdram.o \
	ci/cicardwrcart.o

EDX_OBJ := \
	edx/edxinit.o \
	edx/edxexit.o \
	edx/edxcard.o \
	edx/edxcardinit.o \
	edx/edxcardrddram.o \
	edx/edxcardrdcart.o \
	edx/edxcardwrdram.o \
	edx/edxcardwrcart.o

ED_OBJ := \
	ed/edinit.o \
	ed/edexit.o \
	ed/edcard.o \
	ed/edcardinit.o \
	ed/edcardrddram.o \
	ed/edcardrdcart.o \
	ed/edcardwrdram.o \
	ed/edcardwrcart.o

SC_OBJ := \
	sc/sc.o \
	sc/scinit.o \
	sc/scexit.o \
	sc/sccardinit.o \
	sc/sccardrddram.o \
	sc/sccardrdcart.o \
	sc/sccardwrdram.o \
	sc/sccardwrcart.o

OBJ := \
	cart.o \
	cartbuf.o \
	sd.o \
	sdcrc16.o \
	$(CART_OBJ) \
	$(CI_OBJ) \
	$(EDX_OBJ) \
	$(ED_OBJ) \
	$(SC_OBJ)

INCLUDE := \
	include/cart.h

SRC := \
	src/cartint.h \
	src/cart.c \
	src/cartbuf.c \
	src/sd.h \
	src/sd.c \
	src/sdcrc16.c \
	src/cart/cartinit.c \
	src/cart/cartexit.c \
	src/cart/cartcardinit.c \
	src/cart/cartcardrddram.c \
	src/cart/cartcardrdcart.c \
	src/cart/cartcardwrdram.c \
	src/cart/cartcardwrcart.c \
	src/ci/ci.h \
	src/ci/ci.c \
	src/ci/ciinit.c \
	src/ci/ciexit.c \
	src/ci/cicardinit.c \
	src/ci/cicardrddram.c \
	src/ci/cicardrdcart.c \
	src/ci/cicardwrdram.c \
	src/ci/cicardwrcart.c \
	src/edx/edx.h \
	src/edx/edxinit.c \
	src/edx/edxexit.c \
	src/edx/edxcard.c \
	src/edx/edxcardinit.c \
	src/edx/edxcardrddram.c \
	src/edx/edxcardrdcart.c \
	src/edx/edxcardwrdram.c \
	src/edx/edxcardwrcart.c \
	src/ed/ed.h \
	src/ed/edinit.c \
	src/ed/edexit.c \
	src/ed/edcard.c \
	src/ed/edcardinit.c \
	src/ed/edcardrddram.c \
	src/ed/edcardrdcart.c \
	src/ed/edcardwrdram.c \
	src/ed/edcardwrcart.c \
	src/sc/sc.h \
	src/sc/sc.c \
	src/sc/scinit.c \
	src/sc/scexit.c \
	src/sc/sccardinit.c \
	src/sc/sccardrddram.c \
	src/sc/sccardrdcart.c \
	src/sc/sccardwrdram.c \
	src/sc/sccardwrcart.c

U64_PREFIX  := mips-linux-gnu-
U64_CC      := $(U64_PREFIX)gcc
U64_AR      := $(U64_PREFIX)ar
U64_ARCH    := -mabi=32 -march=vr4300 -mfix4300
U64_OPT     := -Os
U64_WARN    := -Wall -Wextra -Wpedantic -Werror=implicit-function-declaration
U64_CPPFLAGS = -Ilibultra/include -Iinclude -Isrc -D_ULTRA64
U64_CFLAGS = $(U64_ARCH) -mno-abicalls -fno-PIC -mno-check-zero-division -fno-builtin -ffast-math -ftrapping-math -fno-associative-math -fsingle-precision-constant -G 0 $(U64_OPT) $(U64_WARN)
U64_ASFLAGS = $(U64_ARCH) -mno-abicalls -fno-PIC -G 0 $(U64_FLAG) $(U64_OPT)

.PHONY: default
default: lib/libcart.a lib/ultra/cart.h lib/ultra/libcart.c lib/dragon/cart.h lib/dragon/libcart.c

.PHONY: clean
clean:
	rm -f -r build lib

lib/libcart.a: $(addprefix build/,$(OBJ))
	@mkdir -p $(dir $@)
	$(U64_AR) rc $@ $^

build/%.o: src/%.s
	@mkdir -p $(dir $@)
	$(U64_CC) $(U64_ASFLAGS) -c -o $@ $<

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(U64_CC) $(U64_CPPFLAGS) $(U64_CFLAGS) -c -o $@ $<

lib/ultra/cart.h: $(INCLUDE)
	@mkdir -p $(dir $@)
	tools/cat -D_ULTRA64 -h $(INCLUDE) > $@

lib/ultra/libcart.c: $(SRC)
	@mkdir -p $(dir $@)
	tools/cat -D_ULTRA64 -c $(SRC) > $@

lib/dragon/cart.h: $(INCLUDE)
	@mkdir -p $(dir $@)
	tools/cat -h $(INCLUDE) > $@

lib/dragon/libcart.c: $(SRC)
	@mkdir -p $(dir $@)
	tools/cat -c $(SRC) > $@
