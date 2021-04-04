# -*-Makefile-*-

OBJDIRS		+= $(KERN_OBJDIR)/pmm/MATOp

KERN_SRCFILES	+= $(KERN_DIR)/pmm/MATOp/MATOp.c
ifdef TEST
KERN_SRCFILES	+= $(KERN_DIR)/pmm/MATOp/test.c
endif

$(KERN_OBJDIR)/pmm/MATOp/MATOp.o: $(KERN_DIR)/pmm/MATOp/MATOp.c
	@echo + $(COMP_NAME)[KERN/pmm/MATOp] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MATOp: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/pmm/MATOp/$(notdir $@) $@
else
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<
endif

$(KERN_OBJDIR)/pmm/MATOp/test.o: $(KERN_DIR)/pmm/MATOp/test.c
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<

$(KERN_OBJDIR)/pmm/MATOp/%.o: $(KERN_DIR)/pmm/MATOp/%.S
	@echo + as[KERN/pmm/MATOp] $<
	@mkdir -p $(@D)
ifdef SOL 
	$(V)echo "Copying solution MATOp: " + $(notdir $@) 
	$(V)cp $(SAMPLE_KERN_DIR)/pmm/MATOp/$(notdir $@) $@
else
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<
endif
