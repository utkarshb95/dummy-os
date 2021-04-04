# -*-Makefile-*-
TEST=test.c
OBJDIRS		+= $(KERN_OBJDIR)/pmm/MATIntro

KERN_SRCFILES	+= $(KERN_DIR)/pmm/MATIntro/MATIntro.c
ifdef TEST
KERN_SRCFILES	+= $(KERN_DIR)/pmm/MATIntro/test.c
endif

$(KERN_OBJDIR)/pmm/MATIntro/MATIntro.o: $(KERN_DIR)/pmm/MATIntro/MATIntro.c
	@echo + $(COMP_NAME)[KERN/pmm/MATIntro] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MATIntro: " + $(notdir $@)
	$(V)cp $(SAMPLE_KERN_DIR)/pmm/MATIntro/$(notdir $@) $@
else
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<
endif

$(KERN_OBJDIR)/pmm/MATIntro/test.o: $(KERN_DIR)/pmm/MATIntro/test.c
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<

$(KERN_OBJDIR)/pmm/MATIntro/%.o: $(KERN_DIR)/pmm/MATIntro/%.S
	@echo + as[KERN/pmm/MATIntro] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MATIntro: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/pmm/MATIntro/$(notdir $@) $@
else
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<
endif
