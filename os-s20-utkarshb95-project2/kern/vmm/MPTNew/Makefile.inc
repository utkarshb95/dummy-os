# -*-Makefile-*-

OBJDIRS		+= $(KERN_OBJDIR)/vmm/MPTNew

KERN_SRCFILES	+= $(KERN_DIR)/vmm/MPTNew/MPTNew.c
ifdef TEST
KERN_SRCFILES	+= $(KERN_DIR)/vmm/MPTNew/test.c
endif

$(KERN_OBJDIR)/vmm/MPTNew/MPTNew.o: $(KERN_DIR)/vmm/MPTNew/MPTNew.c
	@echo + $(COMP_NAME)[KERN/vmm/MPTNew] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MPTNew: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/vmm/MPTNew/$(notdir $@) $@
else
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<
endif

$(KERN_OBJDIR)/vmm/MPTNew/test.o: $(KERN_DIR)/vmm/MPTNew/test.c
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<

$(KERN_OBJDIR)/vmm/MPTNew/%.o: $(KERN_DIR)/vmm/MPTNew/%.S
	@echo + as[KERN/vmm/MPTNew] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MPTNew: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/vmm/MPTNew/$(notdir $@) $@
else
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<
endif
