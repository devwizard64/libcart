#                libcart - Nintendo 64 flash cartridge library
#                     Copyright (C) 2022 - 2023 devwizard
#      This project is licensed under the terms of the MIT license.  See
#      LICENSE for more information.

OBJ := \
	cart.o              \
	cartbuf.o           \
	sd.o                \
	sdcrc16.o           \
	cartinit.o          \
	cartexit.o          \
	cartcardinit.o      \
	cartcardrddram.o    \
	cartcardrdcart.o    \
	cartcardwrdram.o    \
	cartcardwrcart.o    \
	cartcardswap.o      \
	ci.o                \
	ciinit.o            \
	ciexit.o            \
	cicardinit.o        \
	cicardrddram.o      \
	cicardrdcart.o      \
	cicardwrdram.o      \
	cicardwrcart.o      \
	cicardswap.o        \
	edxinit.o           \
	edxexit.o           \
	edxcard.o           \
	edxcardinit.o       \
	edxcardrddram.o     \
	edxcardrdcart.o     \
	edxcardwrdram.o     \
	edxcardwrcart.o     \
	edxcardswap.o       \
	edinit.o            \
	edexit.o            \
	edcard.o            \
	edcardinit.o        \
	edcardrddram.o      \
	edcardrdcart.o      \
	edcardwrdram.o      \
	edcardwrcart.o      \
	edcardswap.o        \
	sc.o                \
	scinit.o            \
	scexit.o            \
	sccardinit.o        \
	sccardrddram.o      \
	sccardrdcart.o      \
	sccardwrdram.o      \
	sccardwrcart.o      \
	sccardswap.o

U64_HOST    := mips-linux-gnu
U64_CC      := $(U64_HOST)-gcc
U64_AR      := $(U64_HOST)-ar
U64_ARCH    := -mabi=32 -march=vr4300 -mfix4300 -mno-abicalls -fno-PIC -G 0
U64_FLAG    := -Iultra/include -Iinclude -D_ULTRA64
U64_OPT     := -Os
U64_WARN    := -Wall -Wextra -Wpedantic
U64_CCFLAG  := $(U64_ARCH) -mno-check-zero-division -ffreestanding
U64_CCFLAG  += -fno-common -fno-toplevel-reorder
U64_CCFLAG  += $(U64_FLAG) $(U64_OPT) $(U64_WARN)
U64_ASFLAG  := $(U64_ARCH) $(U64_FLAG) $(U64_OPT)

N64_CC      := $(N64_INST)/bin/mips64-elf-gcc
N64_AR      := $(N64_INST)/bin/mips64-elf-ar
N64_ARCH    := -march=vr4300 -mtune=vr4300
N64_FLAG    := -I$(N64_INST)/mips64-elf/include -Iinclude -DN64
N64_OPT     := -O2
N64_WARN    := -Wall -Wextra -Wno-ignored-qualifiers
N64_CCFLAG  := $(N64_ARCH) -falign-functions=32 -ffunction-sections -fdata-sections
N64_CCFLAG  += $(N64_FLAG) $(N64_OPT) $(N64_WARN)
N64_ASFLAG  := $(N64_ARCH)

.PHONY: default
default: lib/libcart_ultra.a lib/libcart_dragon.a

.PHONY: clean
clean:
	rm -f -r build lib

lib/libcart_ultra.a: $(addprefix build/ultra/,$(OBJ))
	@mkdir -p $(dir $@)
	$(U64_AR) rc $@ $^

build/ultra/%.o: src/%.s
	@mkdir -p $(dir $@)
	$(U64_CC) $(U64_ASFLAG) -c -o $@ $<

build/ultra/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(U64_CC) $(U64_CCFLAG) -c -o $@ $<

lib/libcart_dragon.a: $(addprefix build/dragon/,$(OBJ))
	@mkdir -p $(dir $@)
	$(N64_AR) rc $@ $^

build/dragon/%.o: src/%.s
	@mkdir -p $(dir $@)
	$(N64_CC) $(N64_ASFLAG) -c -o $@ $<

build/dragon/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(N64_CC) $(N64_CCFLAG) -c -o $@ $<
