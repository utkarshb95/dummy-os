# -*-Makefile-*-

OBJDIRS		+= $(KERN_OBJDIR)/vmm/MPTOp

KERN_SRCFILES	+= $(KERN_DIR)/vmm/MPTOp/MPTOp.c
ifdef TEST
KERN_SRCFILES	+= $(KERN_DIR)/vmm/MPTOp/test.c
endif

$(KERN_OBJDIR)/vmm/MPTOp/MPTOp.o: $(KERN_DIR)/vmm/MPTOp/MPTOp.c
	@echo + $(COMP_NAME)[KERN/vmm/MPTOp] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MPTOp: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/vmm/MPTOp/$(notdir $@) $@
else
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<
endif

$(KERN_OBJDIR)/vmm/MPTOp/test.o: $(KERN_DIR)/vmm/MPTOp/test.c
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<

$(KERN_OBJDIR)/vmm/MPTOp/%.o: $(KERN_DIR)/vmm/MPTOp/%.S
	@echo + as[KERN/vmm/MPTOp] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MPTOp: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/vmm/MPTOp/$(notdir $@) $@
else
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<
endif
