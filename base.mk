CC	:= mips64-elf-gcc
AS	:= mips64-elf-as
LD	:= mips64-elf-ld
OBJCOPY	:= mips64-elf-objcopy
OBJDUMP	:= mips64-elf-objdump

emudir	:= $(DEVKITPRO)/emulators
nopsx	:= $(emudir)/psx/nopsx/NO\$$PSX.EXE

build/%.o : %.S
	$(CC) $(asflags) -MMD -c $< -o $@

build/%.o : %.c
	$(CC) $(cflags) -MMD -c $< -o $@

%.exe : %.elf
	$(OBJCOPY) -O binary $< $@

%.elf :
	$(CC) $(ldflags) -o $@ $(ofiles)

