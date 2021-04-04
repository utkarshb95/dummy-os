#include <lib/string.h>
#include <lib/trap.h>
#include <lib/syscall.h>
#include <lib/debug.h>
#include <lib/x86.h>
#include <dev/intr.h>

#include <vmm/MPTOp/export.h>

#include "import.h"

extern tf_t uctx_pool[NUM_IDS];

static void trap_dump(tf_t *tf)
{
	if (tf == NULL)
		return;

	uintptr_t base = (uintptr_t) tf;

	KERN_DEBUG("trapframe at %x\n", base);
	KERN_DEBUG("\t%08x:\tedi:   \t\t%08x\n", &tf->regs.edi, tf->regs.edi);
	KERN_DEBUG("\t%08x:\tesi:   \t\t%08x\n", &tf->regs.esi, tf->regs.esi);
	KERN_DEBUG("\t%08x:\tebp:   \t\t%08x\n", &tf->regs.ebp, tf->regs.ebp);
	KERN_DEBUG("\t%08x:\tesp:   \t\t%08x\n", &tf->regs.oesp, tf->regs.oesp);
	KERN_DEBUG("\t%08x:\tebx:   \t\t%08x\n", &tf->regs.ebx, tf->regs.ebx);
	KERN_DEBUG("\t%08x:\tedx:   \t\t%08x\n", &tf->regs.edx, tf->regs.edx);
	KERN_DEBUG("\t%08x:\tecx:   \t\t%08x\n", &tf->regs.ecx, tf->regs.ecx);
	KERN_DEBUG("\t%08x:\teax:   \t\t%08x\n", &tf->regs.eax, tf->regs.eax);
	KERN_DEBUG("\t%08x:\tes:    \t\t%08x\n", &tf->es, tf->es);
	KERN_DEBUG("\t%08x:\tds:    \t\t%08x\n", &tf->ds, tf->ds);
	KERN_DEBUG("\t%08x:\ttrapno:\t\t%08x\n", &tf->trapno, tf->trapno);
	KERN_DEBUG("\t%08x:\terr:   \t\t%08x\n", &tf->err, tf->err);
	KERN_DEBUG("\t%08x:\teip:   \t\t%08x\n", &tf->eip, tf->eip);
	KERN_DEBUG("\t%08x:\tcs:    \t\t%08x\n", &tf->cs, tf->cs);
	KERN_DEBUG("\t%08x:\teflags:\t\t%08x\n", &tf->eflags, tf->eflags);
	KERN_DEBUG("\t%08x:\tesp:   \t\t%08x\n", &tf->esp, tf->esp);
	KERN_DEBUG("\t%08x:\tss:    \t\t%08x\n", &tf->ss, tf->ss);
}

void default_exception_handler(void)
{
	unsigned int cur_pid;

	cur_pid = get_curid();
	trap_dump(&uctx_pool[cur_pid]);

	KERN_PANIC("Trap %d @ 0x%08x.\n", uctx_pool[cur_pid].trapno, uctx_pool[cur_pid].eip);
}

void pgflt_handler(void)
{
	unsigned int cur_pid;
	unsigned int errno;
	unsigned int fault_va;
	unsigned int pte_entry;

	cur_pid = get_curid();
	errno = uctx_pool[cur_pid].err;
	fault_va = rcr2();

	/* If implementing copy-on-write semantics, need to handle errno == 0x3 
	 * In that case, check if the page table entry [fault_va] is marked as PTE_COW 
	 * and copy it and return.
	 */

  //Uncomment this line if you need to see the information of the sequence of page faults occured.
	//KERN_DEBUG("Page fault: VA 0x%08x, errno 0x%08x, process %d, EIP 0x%08x.\n", fault_va, errno, cur_pid, uctx_pool[cur_pid].eip);

	if (errno & PFE_PR) {
		KERN_PANIC("Permission denied: va = 0x%08x, errno = 0x%08x.\n", fault_va, errno);
		return;
	}

	if (alloc_page(cur_pid, fault_va, PTE_W | PTE_U | PTE_P) == MagicNumber)
    KERN_PANIC("Page allocation failed: va = 0x%08x, errno = 0x%08x.\n", fault_va, errno);

}

void exception_handler(void)
{
    unsigned int curid, syscall_num; 
  
    curid = get_curid();
    syscall_num = uctx_pool[curid].trapno;
  
    switch (syscall_num) {
      case T_PGFLT:
        pgflt_handler();
        break;
  
      default: 
        default_exception_handler();
   }
}

static int spurious_intr_handler (void)
{
    return 0;
}

static int timer_intr_handler (void)
{
    intr_eoi ();
    return 0;
}

static int default_intr_handler (void)
{
    intr_eoi ();
    return 0;
}

void interrupt_handler (void)
{
    unsigned int curid, intr;
  
    curid = get_curid();
    intr = uctx_pool[curid].trapno;
  
    // dprintf("interrupt handler: intr = %d", intr);
  
    switch (intr) {
      case T_IRQ0 + IRQ_SPURIOUS:  // at: in dev/intr.h
        spurious_intr_handler();
        break;
  
      case T_IRQ0 + IRQ_TIMER: 
        timer_intr_handler();
        break;
  
      default:
        default_intr_handler();
  }
}

/** TASK 1:
  * * Handle all traps.
  *   All traps will enter here from the _alltraps function.
  *   For any trap, you will need to perform the following:
  *   - Save a copy of the trap frame as the current process' user context.
  *       -  User context's are stored in the uctx_pool data structure.
  *   - Switch to the appropriate paging structure to handle the trap.
  *   - Route the trap to appropriate handlers.
  *       - All trap identifiers are defined in: dev/intr.h
  *       - We have 3 types of trap handlers:
  *         1. exception_handler => call if [trapno] is between T_DIVIDE and T_SECEV.
  *         2. interrupt_handler => call if [trapno] is between T_IRQ0 + IRQ_TIMER and T_IRQ0 + IRQ_IDE2
  *         3. syscall_dispatch  => call if [trapno] is T_SYSCALL
  *            You will implement syscall_dispatch() in TDispatch layer. Simply call it
  *            when appropriate.
  *   - After the trap is handled, return from trap.
  *       - The LAST statement of this function is already provided [proc_start_user()]. 
  * 
  *  Hint: 
  *  - Please look at _alltraps functions in idt.S
  */
void trap (tf_t *tf)
{
    // TODO
    uctx_pool[get_curid()] = *tf;
    set_pdir_base(0);

    if(tf->trapno >= T_DIVIDE && tf->trapno <= T_SECEV)
      exception_handler();
    
    else if(tf->trapno >= T_IRQ0 + IRQ_TIMER && tf->trapno <= T_IRQ0 + IRQ_IDE2)
      interrupt_handler();

    else if(tf->trapno == T_SYSCALL)
      syscall_dispatch();

	  // Trap handled: call proc_start_user() to initiate return from trap.
    proc_start_user(); 
}
