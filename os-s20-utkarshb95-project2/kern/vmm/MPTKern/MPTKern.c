#include <lib/x86.h>
#include <lib/debug.h>

#include "import.h"

#define VM_USERLO 0x40000000
#define VM_USERHI 0xF0000000
#define DIR_MASK    0xffc00000
#define PAGE_MASK   0x003ff000
#define OFFSET_MASK 0x00000fff
#define DIR_SHIFT   22
#define PAGE_SHIFT  12
#define PAGESIZE 4096;

/** TASK 1:
  * * Set the entire page map for process 0 as identity map.
  *  
  * Hint 1: Note that part of the task is already completed by pdir_init.
  * Hint 2: Here just set the remaining portion of process 0's page directory entry as identity map.
  */
void pdir_init_kern(unsigned int mbi_adr)
{
    // TODO: define your local variables here.
    unsigned int i, lo, hi;
    pdir_init(mbi_adr);
    
    //TODO
    lo = VM_USERLO / 4096 / 1024;
    hi = VM_USERHI / 4096 / 1024;
    for(i = lo; i < hi; i++){
      set_pdir_entry_identity(0,i);
    }
}

/** TASK 2:
  * * Map the physical page # [page_index] for the given virtual address with the given permission.
  *   - In the case, when the page table for the page directory entry is not set up, you need to allocate the page table first.
  *   - In the case of error, return the constant MagicNumber defined in lib/x86.h,
  *     otherwise, return the physical page index registered in the page directory,
  *     e.g., the return value of get_pdir_entry_by_va or alloc_ptbl.
  * Hint 1: Get the pde for vadr
  * Hint 2: If pde is already set, find the pde index. (pde / PAGESIZE)
  *         Otherwise, first allocate the page table (MPTComm layer)
  *         - If there is an error during allocation, return MagicNumber.
  * Hint 3: If you have a valid pde, set the page table entry to new physical page (page_index) and perm.
  * Hint 4: Return the pde index or MagicNumber.
  */
unsigned int map_page(unsigned int proc_index, unsigned int vadr, unsigned int page_index, unsigned int perm)
{   
  // TODO
  unsigned int pde_index=0, pde=0, addr=0;
  pde = get_pdir_entry_by_va(proc_index, vadr);
  if(pde > 0){
    pde_index = pde>>12;
    // pde_index = pde<<12;
    // pde_index = pde / PAGESIZE;
  }
  else{
    addr = alloc_ptbl(proc_index, vadr);
    if(addr == 0){
      return MagicNumber;
    }
  }
  set_ptbl_entry_by_va(proc_index, vadr, page_index, perm);
  // return get_pdir_entry_by_va(proc_index, vadr);
  // return get_ptbl_entry_by_va(proc_index, vadr);
  // return pde_index;
  // dprintf("\npde, pde_index, addr = %u, %u, %u\n", pde, pde_index, addr);
  if(addr != 0)
    return addr;
  else
    return pde_index;
}

/** TASK 3:
  * * Remove the mapping for the given virtual address (with rmv_ptbl_entry_by_va).
  * Hint 1: You need to first make sure that the mapping is still valid,
  *         by reading the page table entry (pte) for the virtual address.
  *         - Nothing should be done if the mapping no longer exists.
  * Hint 2: If pte is valid, remove page table entry for vadr.
  * Hint 3: Return the corresponding page table entry.
  */
unsigned int unmap_page(unsigned int proc_index, unsigned int vadr)
{
  // TODO
  unsigned int pte=0;
  pte = get_ptbl_entry_by_va(proc_index, vadr);
  // dprintf("pte = %u\n", pte);
  if(pte != 0){
    rmv_ptbl_entry_by_va(proc_index, vadr);
  }

  return pte;
}   
