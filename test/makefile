include ../base.mk

libpsx	:= ../libpsx

target	:= $(shell basename $(CURDIR))
output	:= $(target)
build	:= build
sources	:= . $(libpsx)/src
incdirs	:= . $(libpsx)/include $(build)
includes:= $(foreach dir,$(incdirs),-I$(dir))

arch	:= -march=r3000 -mabi=32 -EL -msoft-float -Wa,-msoft-float
asflags	:= -g $(arch)
cflags	:= -g -std=c99 -Wall -Wextra -pedantic -mgpopt -mno-extern-sdata -pipe $(arch)
ldflags	:= $(cflags) -Wl,-Map=$(target).map -nostdlib -T$(libpsx)/psx-exe.ld

sfiles	:= $(foreach dir,$(sources),$(notdir $(wildcard $(dir)/*.S)))
cfiles	:= $(foreach dir,$(sources),$(notdir $(wildcard $(dir)/*.c)))

ofiles	:= $(cfiles:%.c=$(build)/%.o) $(sfiles:%.S=$(build)/%.o)
depfiles:= $(ofiles:.o=.d)

VPATH	:= $(foreach dir,$(sources),$(CURDIR)/$(dir))

.PHONY: all clean debug release run

all: release

debug: asflags	+= -DDEBUG
debug: cflags	+= -O0 -DDEBUG
debug: ldflags	+=
debug: $(output).exe

release: asflags	+=
release: cflags		+= -Os -flto -ffat-lto-objects
release: ldflags	+= -flto -ffat-lto-objects
release: $(output).exe

$(output).exe : $(output).bin

$(output).bin : $(output).elf

$(output).elf : $(build) $(ofiles)

$(build):
	@mkdir -p $@

clean:
	rm -rf $(output).exe $(output).bin $(output).elf $(output).map $(build)

run:
	$(nopsx) $(output).exe

dump:
	$(OBJDUMP) -b binary -mmips:3000 -EL -D $(output).bin

-include $(depfiles)

