prefix	:= mips64-elf-
CC	:= $(prefix)gcc
AS	:= $(prefix)as
LD	:= $(prefix)ld
OBJCOPY	:= $(prefix)objcopy
OBJDUMP	:= $(prefix)objdump
bin2exe	= python $(libpsx)/tools/bin2exe.py

emudir	:= $(DEVKITPRO)/emulators
nopsx	:= $(emudir)/psx/nopsx/NO\$$PSX.EXE

.DEFAULT_GOAL	:= all

build/%.o : %.S
	$(CC) $(asflags) $(includes) -MMD -c $< -o $@

build/%.o : %.c
	$(CC) $(cflags) $(includes) -MMD -c $< -o $@

%.exe : %.bin
	$(bin2exe) $< $@

%.bin : %.elf
	$(OBJCOPY) -O binary $< $@

%.elf :
	$(CC) $(ldflags) -o $@ $(ofiles)

