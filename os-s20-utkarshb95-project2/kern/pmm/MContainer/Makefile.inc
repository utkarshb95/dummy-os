# -*-Makefile-*-

OBJDIRS		+= $(KERN_OBJDIR)/pmm/MContainer

KERN_SRCFILES	+= $(KERN_DIR)/pmm/MContainer/MContainer.c
ifdef TEST
KERN_SRCFILES	+= $(KERN_DIR)/pmm/MContainer/test.c
endif

$(KERN_OBJDIR)/pmm/MContainer/MContainer.o: $(KERN_DIR)/pmm/MContainer/MContainer.c
	@echo + $(COMP_NAME)[KERN/pmm/MContainer] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MContainer: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/pmm/MContainer/$(notdir $@) $@
else
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<
endif

$(KERN_OBJDIR)/pmm/MContainer/test.o: $(KERN_DIR)/pmm/MContainer/test.c
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<

$(KERN_OBJDIR)/pmm/MContainer/%.o: $(KERN_DIR)/pmm/MContainer/%.S
	@echo + as[KERN/pmm/MContainer] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MContainer: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/pmm/MContainer/$(notdir $@) $@
else
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<
endif
