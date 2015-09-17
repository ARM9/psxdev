CC	:= mips64-elf-gcc
AS	:= mips64-elf-as
LD	:= mips64-elf-ld
OBJCOPY	:= mips64-elf-objcopy
OBJDUMP	:= mips64-elf-objdump
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

