OPTIONS=-DF_CPU=48000000 -D__MKL26Z64__
CPU=cortex-m0plus

CFLAGS=-ffunction-sections -Wall -Os -mcpu=$(CPU) -mthumb -MMD -I. $(OPTIONS)

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

LINKER_SCRIPT=mkl26z64.ld

LDFLAGS=-Os -Wl,--gc-sections,--defsym=__rtc_localtime=0 --specs=nano.specs -mcpu=${CPU} -mthumb -T${LINKER_SCRIPT}

OBJS=main.o mk20dx128.o pins_teensy.o analog.o

all: main.hex

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

main.elf: $(OBJS) ${LINKER_SCRIPT}
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f *.o *.d main.elf main.hex

