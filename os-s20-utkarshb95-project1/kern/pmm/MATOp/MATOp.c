#include <lib/debug.h>
#include "import.h"

/** TASK 1:
  * Allocation of a physical page.
  *
  * 1. - First, implement a naive page allocator that scans the data-structure
  *      you implemented in MATIntro.
  *
  *    Hint 1: (Q: Do you have to scan the physical pages from index 0?
  *    Recall how you have initialized the table in pmem_init.)
  *
  *    - Then mark the page as allocated in the data-structure and return the
  *      page index of the page found.
  *      In the case when there is no available page found, return 0.
  * 2. Optimize the code with the memorization techniques so that you do not
  *    have to scan the data-structure from scratch every time.
  */
unsigned int
palloc()
{
  // TODO
  return 0;
}


/** TASK 2:
  * Free of a physical page.
  *
  * This function marks the page with given index as unallocated in your
  * data-structure.
  *
  * Hint: Simple. Check if a page is allocated and to set the allocation status
  *       of a page index.
  */
void
pfree(unsigned int pfree_index)
{
  // TODO
}
