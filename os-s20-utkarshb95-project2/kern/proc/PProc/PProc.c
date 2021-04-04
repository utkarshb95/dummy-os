#include <lib/elf.h>
#include <lib/debug.h>
#include <lib/gcc.h>
#include <lib/seg.h>
#include <lib/trap.h>
#include <lib/x86.h>

#include "import.h"

extern tf_t uctx_pool[NUM_IDS];

/** TASK 1:
  * * Initiate return from trap.
  *   Once the trap is handled, the OS will switch back from the kernel to the user process.
  *   For this you will:
  *   - Switch the Task State Segment (TSS) to the current user process.
  * 	TSS switch is done in tss_switch(). Part of this task is to:
  * 		- Understand the TSS data structure
  * 		- How is it initialized?
  *			- How does the hardware use this? When does it use it?
  *   - Set the page structures to the current user process.
  *   - call trap_return() with the pointer to the current process' user context.
  *     - User context's are stored in uctx_pool.
  */
void proc_start_user(void)
{
	// TODO
  unsigned int curid = get_curid();
  tss_switch(curid);
  set_pdir_base(curid);
  trap_return(&uctx_pool[curid]);
}

/** 
  * * Create a new process.
  *   1. Create a new child thread context.
  *       - This is implemented in thread_spawn()
  *       - ALL NEW THREADS MUST first enter proc_start_user() function.
  *   2. Load the elf pointed to by [elf_addr] into virtual address space 
  *     of the new child process.
  *       - This is implemented in elf_load() function in elf.c.
  *   3. Setup the user context for this new process in uctx_pool
  *       - set the initial values for the user context as follows:
  *         %es ==> offset to User Data segment in the GDT with user level permissions.
  *         %ds ==> offset to User Data segment in the GDT with user level permissions.
  *         %cs ==> offset to User Code segment in the GDT with user level permissions.
  *         %ss ==> offset to User Data segment in the GDT with user level permissions.
  *         %esp ==> VM_USERHI.
  *         %eflags ==> Set Interrupt flag.
  *         %eip ==> Entry point for the elf to be loaded.
  *           - The entry point for the given elf [elf_addr] can be retrieved using 
  *             elf_entry() function defined in elf.c
  *   4. Return: the pid of the new thread. 
  */
unsigned int proc_create(void *elf_addr, unsigned int quota)
{
	  unsigned int id = get_curid(), pid = thread_spawn((void *) proc_start_user, id, quota);
	  
    elf_load(elf_addr, pid);
    uctx_pool[pid].es = CPU_GDT_UDATA | 3;
    uctx_pool[pid].ds = CPU_GDT_UDATA | 3;
    uctx_pool[pid].cs = CPU_GDT_UCODE | 3;
    uctx_pool[pid].ss = CPU_GDT_UDATA | 3;
    uctx_pool[pid].esp = VM_USERHI;
    uctx_pool[pid].eflags = FL_IF;
    uctx_pool[pid].eip = elf_entry(elf_addr);

	  return pid;
}
