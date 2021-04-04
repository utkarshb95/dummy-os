# -*-Makefile-*-

BOOT0_OBJFILES += $(OBJDIR)/boot/boot0.o

$(OBJDIR)/boot/boot0: $(BOOT0_OBJFILES)
	@echo + ld[BOOT] $@
	$(V)$(LD) $(BOOT_LDFLAGS) -N -e start -Ttext 0x7c00 -o $@.elf $^
	$(V)$(OBJDUMP) -S -M i8086 $@.elf > $@.asm
	$(V)$(OBJCOPY) -S -O binary $@.elf $@
	$(V)$(NM) -n $@.elf > $@.sym
	$(V)$(PERL) $(UTILSDIR)/check_size.pl 446 $@

$(OBJDIR)/boot/%.o: boot/boot0/%.S
	$(V)echo + as[BOOT] $<
	$(V)mkdir -p $(@D)
ifdef SOL
	$(V)echo "Copying solution boot0." + $(notdir $@)
	$(V)cp $(SAMPLEDIR)/boot/boot0.o $@
else 
	$(V)$(CC) -nostdinc $(BOOT_CFLAGS) -Os -c -o $@ $<
endif
