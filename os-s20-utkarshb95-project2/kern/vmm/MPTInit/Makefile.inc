# -*-Makefile-*-

OBJDIRS		+= $(KERN_OBJDIR)/vmm/MPTInit

KERN_SRCFILES	+= $(KERN_DIR)/vmm/MPTInit/MPTInit.c

$(KERN_OBJDIR)/vmm/MPTInit/MPTInit.o: $(KERN_DIR)/vmm/MPTInit/MPTInit.c
	@echo + $(COMP_NAME)[KERN/vmm/MPTInit] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MPTInit: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/vmm/MPTInit/$(notdir $@) $@
else
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<
endif

$(KERN_OBJDIR)/vmm/MPTInit/test.o: $(KERN_DIR)/vmm/MPTInit/test.c
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<

$(KERN_OBJDIR)/vmm/MPTInit/%.o: $(KERN_DIR)/vmm/MPTInit/%.S
	@echo + as[KERN/vmm/MPTInit] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MPTInit: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/vmm/MPTInit/$(notdir $@) $@
else
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<
endif
