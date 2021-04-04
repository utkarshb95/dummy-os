# -*-Makefile-*-

OBJDIRS		+= $(KERN_OBJDIR)/vmm/MPTComm

KERN_SRCFILES	+= $(KERN_DIR)/vmm/MPTComm/MPTComm.c
ifdef TEST
KERN_SRCFILES	+= $(KERN_DIR)/vmm/MPTComm/test.c
endif

$(KERN_OBJDIR)/vmm/MPTComm/MPTComm.o: $(KERN_DIR)/vmm/MPTComm/MPTComm.c
	@echo + $(COMP_NAME)[KERN/vmm/MPTComm] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MPTComm: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/vmm/MPTComm/$(notdir $@) $@
else
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<
endif

$(KERN_OBJDIR)/vmm/MPTComm/test.o: $(KERN_DIR)/vmm/MPTComm/test.c
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<

$(KERN_OBJDIR)/vmm/MPTComm/%.o: $(KERN_DIR)/vmm/MPTComm/%.S
	@echo + as[KERN/vmm/MPTComm] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MPTComm: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/vmm/MPTComm/$(notdir $@) $@
else
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<
endif
