# -*-Makefile-*-

OBJDIRS		+= $(KERN_OBJDIR)/vmm/MPTKern

KERN_SRCFILES	+= $(KERN_DIR)/vmm/MPTKern/MPTKern.c
ifdef TEST
KERN_SRCFILES	+= $(KERN_DIR)/vmm/MPTKern/test.c
endif

$(KERN_OBJDIR)/vmm/MPTKern/MPTKern.o: $(KERN_DIR)/vmm/MPTKern/MPTKern.c
	@echo + $(COMP_NAME)[KERN/vmm/MPTKern] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MPTKern: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/vmm/MPTKern/$(notdir $@) $@
else
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<
endif

$(KERN_OBJDIR)/vmm/MPTKern/test.o: $(KERN_DIR)/vmm/MPTKern/test.c
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<

$(KERN_OBJDIR)/vmm/MPTKern/%.o: $(KERN_DIR)/vmm/MPTKern/%.S
	@echo + as[KERN/vmm/MPTKern] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MPTKern: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/vmm/MPTKern/$(notdir $@) $@
else
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<
endif
