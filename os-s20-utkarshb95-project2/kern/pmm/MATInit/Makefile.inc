# -*-Makefile-*-

OBJDIRS		+= $(KERN_OBJDIR)/pmm/MATInit

KERN_SRCFILES	+= $(KERN_DIR)/pmm/MATInit/MATInit.c
ifdef TEST
KERN_SRCFILES	+= $(KERN_DIR)/pmm/MATInit/test.c
endif

$(KERN_OBJDIR)/pmm/MATInit/MATInit.o: $(KERN_DIR)/pmm/MATInit/MATInit.c
	@echo + $(COMP_NAME)[KERN/pmm/MATInit] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MATInit: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/pmm/MATInit/$(notdir $@) $@
else
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<
endif

$(KERN_OBJDIR)/pmm/MATInit/test.o: $(KERN_DIR)/pmm/MATInit/test.c
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<

$(KERN_OBJDIR)/pmm/MATInit/%.o: $(KERN_DIR)/pmm/MATInit/%.S
	@echo + as[KERN/pmm/MATInit] $<
	@mkdir -p $(@D)
ifdef SOL
	$(V)echo "Copying solution MATInit: " + $(notdir $@)
	$(V)cp $(SAMPLE_KERN_DIR)/pmm/MATInit/$(notdir $@) $@
else
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<
endif
