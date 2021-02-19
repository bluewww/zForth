
BIN	:= zforth
SRC	:= main.c zforth.c libc.c udma.c

IHX	:= $(BIN).ihx
OBJS    := $(subst .c,.o, $(SRC))
OBJS    += crt0.o setjmp.o
DEPS    := $(subst .c,.d, $(SRC))

CC	:= riscv32-unknown-elf-gcc
ARCH    := -march=rv32imc -mabi=ilp32

VPATH   := ../zforth
CFLAGS	+= -I. -I../zforth -Iinclude/hal -Iinclude/archi -Iinclude

CFLAGS	+= $(ARCH) -Os -g -MMD -ffunction-sections -fdata-sections -ffreestanding
CFLAGS	+= -Wall -Wextra -Wno-unused-parameter -Wno-clobbered -Wno-unused-result
#CFLAGS  += -save-temps -P

ASFLAGS = $(ARCH) -Os -g -MMD -ffunction-sections -fdata-sections -ffreestanding

LDFLAGS	+= -T link.ld -g -Wl,--gc-sections -nostdlib -Wl,-Map,zforth.map $(ARCH)
CFLAGS  += -flto
LDFLAGS += -flto
ASFLAGS += -flto

all: $(IHX)

$(IHX): $(BIN)
#riscv32-unknown-elf-objcopy -j .text -j .data -O ihex $(BIN) $(IHX)
	riscv32-unknown-elf-size $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f $(IHX) $(BIN) $(OBJS) $(DEPS)

-include $(DEPS)

