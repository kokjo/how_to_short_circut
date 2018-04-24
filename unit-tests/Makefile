PACKAGE    = test
ADD_CFLAGS = -Wno-main -I. -Igecklib/include -Igecklib
ADD_LFLAGS =

TRGT      ?= arm-none-eabi-
CC         = $(TRGT)gcc
OBJCOPY    = $(TRGT)objcopy

LDSCRIPT   = tomu.ld
DBG_CFLAGS = -ggdb -g -DDEBUG -Wall
DBG_LFLAGS = -ggdb -g -Wall
CFLAGS     = $(ADD_CFLAGS) \
             -Wall -Werror -Wextra \
             -mcpu=cortex-m0plus -mfloat-abi=soft -mthumb \
             -ffunction-sections -fdata-sections -fno-common \
             -fomit-frame-pointer -Os
CXXFLAGS   = $(CFLAGS) -std=c++11 -fno-rtti -fno-exceptions
LFLAGS     = $(ADD_LFLAGS) $(CFLAGS) \
             -nostartfiles \
             -Wl,--gc-sections \
             -Wl,--no-warn-mismatch,--script=$(LDSCRIPT),--build-id=none

OBJ_DIR    = .obj

CSOURCES   = main.c $(wildcard gecklib/*.c)
CPPSOURCES = $(wildcard *.cpp)
ASOURCES   = $(wildcard *.S)
COBJS      = $(addprefix $(OBJ_DIR)/, $(CSOURCES:.c=.o))
OBJECTS    = $(COBJS) $(CXXOBJS) $(AOBJS)
VPATH      = .

QUIET      =

ALL        = all
TARGET     = $(PACKAGE).elf
CLEAN      = clean

$(ALL): $(TARGET)

$(OBJECTS): | $(OBJ_DIR)

$(TARGET): $(OBJECTS) $(LDSCRIPT)
	$(QUIET) echo "  LD       $@"
	$(QUIET) $(CC) $(OBJECTS) $(LFLAGS) -o $@

$(PACKAGE).bin: $(TARGET)
	$(QUIET) echo "  OBJCOPY  $(PACKAGE).bin"
	$(QUIET) $(OBJCOPY) -O binary $(TARGET) $(PACKAGE).bin

$(PACKAGE).ihex: $(TARGET)
	$(QUIET) echo "  IHEX     $(PACKAGE).ihex"
	$(QUIET) $(OBJCOPY) -O ihex $(TARGET) $(PACKAGE).ihex

$(DEBUG): CFLAGS += $(DBG_CFLAGS)
$(DEBUG): LFLAGS += $(DBG_LFLAGS)
CFLAGS += $(DBG_CFLAGS)
LFLAGS += $(DBG_LFLAGS)
$(DEBUG): $(TARGET)

$(OBJ_DIR):
	$(QUIET) mkdir -p $(OBJ_DIR)/gecklib

$(COBJS) : $(OBJ_DIR)/%.o : %.c Makefile
	$(QUIET) echo "  CC       $<	$@"
	$(QUIET) $(CC) -c $< $(CFLAGS) -o $@ -MMD

$(OBJ_DIR)/%.o: %.S
	$(QUIET) echo "  AS       $<	$@"
	$(QUIET) $(CC) -x assembler-with-cpp -c $< $(CFLAGS) -o $@ -MMD

.PHONY: $(CLEAN)

$(CLEAN):
	$(QUIET) rm -f $(wildcard $(OBJ_DIR)/*.d)
	$(QUIET) rm -f $(wildcard $(OBJ_DIR)/*.o)
	$(QUIET) rm -f $(TARGET) $(PACKAGE).bin $(PACKAGE).symbol $(PACKAGE).ihex
	$(QUIET) rm -rf $(OBJ_DIR)

flash: $(PACKAGE).bin
	dfu-util -d 1209:70b1 -D $(PACKAGE).bin

include $(wildcard $(OBJ_DIR)/*.d)
