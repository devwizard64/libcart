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
default: lib/libcart.a

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
