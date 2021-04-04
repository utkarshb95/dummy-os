#include <lib/x86.h>

#include "import.h"

#define VM_USERLO 0x40000000
#define VM_USERHI 0xF0000000
#define DIR_MASK    0xffc00000
#define PAGE_MASK   0x003ff000
#define OFFSET_MASK 0x00000fff
#define DIR_SHIFT   22
#define PAGE_SHIFT  12

/** TASK 1:
  * * For each process from id 0 to NUM_IDS -1,
  *   set the page directory entries so that the kernel portion of the map as identity map,
  *   and the rest of page directories are unmmaped.
  * 
  * Hint 1: Recall which portions are reserved for the kernel and calculate the pde_index.       
  * Hint 2: Recall which function in MPTIntro layer is used to set identity map. (See import.h) 
  * Hint 3: Remove the page directory entry to unmap it.
  */
void pdir_init(unsigned int mbi_adr)
{
    // TODO: define your local variables here.
    unsigned int i, j, lo, hi, addr, size = 1024;
    idptbl_init(mbi_adr);

    // // // TODO
    lo = VM_USERLO / 4096 / 1024;
    hi = VM_USERHI / 4096 / 1024;
    for(i = 0; i < NUM_IDS; i++){
      for(j = 0; j < size; j++){
        if(j < lo || j >= hi)
          set_pdir_entry_identity(i,j);
        else
          rmv_pdir_entry(i,j);
      }
    }
}

/** TASK 2:
  * * 1. Allocate a page (with container_alloc) for the page table,
  * * 2. Check if the page was allocated and register the allocated page in page directory for the given virtual address.
  * * 3. Clear (set to 0) all the page table entries for this newly mapped page table.
  * * 4. Return the page index of the newly allocated physical page.
  * 	 In the case when there's no physical page available, it returns 0.
  */
unsigned int alloc_ptbl(unsigned int proc_index, unsigned int vadr)
{
  // TODO
  unsigned int addr, pde_index, i, size = 1024;
  addr = container_alloc(proc_index);
  pde_index = (vadr & DIR_MASK)>>DIR_SHIFT;
  if(addr > 0){
    // dprintf("addr = %u\n", addr);
    set_pdir_entry_by_va(proc_index, vadr, addr);
    for(i = 0; i < size; i++){
      rmv_ptbl_entry(proc_index, pde_index, i);
    }
    return addr;
  }

  return 0;
}

/** TASK 3:
  * * Reverse operation of alloc_ptbl.
  *   - Remove corresponding page directory entry
  *   - Free the page for the page table entries (with container_free).
  * Hint 1: Find the pde corresponding to vadr (MPTOp layer)
  * Hint 2: Remove the pde (MPTOp layer)
  * Hint 3: Use container free
  */
void free_ptbl(unsigned int proc_index, unsigned int vadr)
{
  // TODO
  unsigned int addr, i, pde;
  pde = get_pdir_entry_by_va(proc_index, vadr);
  rmv_pdir_entry_by_va(proc_index, vadr);
  addr = pde & DIR_MASK;
  container_free(proc_index, addr);
}