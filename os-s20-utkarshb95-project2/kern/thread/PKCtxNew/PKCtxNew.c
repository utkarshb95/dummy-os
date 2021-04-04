#include <lib/gcc.h>
#include <lib/x86.h>

#include "import.h"

extern char STACK_LOC[NUM_IDS][PAGESIZE] gcc_aligned(PAGESIZE);

/** TASK 1:
  * * Allocate memory for the new child thread, then set the eip, and esp
  *   of the thread states. The eip should be set to [entry], and the
  *   esp should be set to the corresponding stack TOP in STACK_LOC.
  *   Don't forget the stack is going down from high address to low.
  *   We do not care about the rest of states when a new thread starts.
  *   The function returns the child thread (process) id.
  *
  *  Hint 1: 
  *  - The alloc_mem_quota function will return the pid of the child process. 
  *    Use this to set the eip and esp in the context using functions defined in import.h.
  *  Hint 2: 
  *  - Set eip to [entry]
  *  - Set esp to corresponding stack TOP in STACK_LOC. 
  *    i.e. Address of STACK_LOC[child][PAGESIZE - 1]. Remember that the stack is going down from high address to low.
  *  Hint 3:
  *  - Return the child pid.
  */
// unsigned int alloc_mem_quota(unsigned int id, unsigned int quota);
// void kctx_set_esp(unsigned int pid, void *esp);
// void kctx_set_eip(unsigned int pid, void *eip);
unsigned int kctx_new(void *entry, unsigned int id, unsigned int quota)
{
  // TODO
  unsigned int pid = alloc_mem_quota(id, quota);
  kctx_set_eip(pid, entry);
  kctx_set_esp(pid, (void*)&STACK_LOC[pid][PAGESIZE-1]);

  return pid;
}
