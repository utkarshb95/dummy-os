#include <lib/gcc.h>
#include <lib/x86.h>
#include <lib/debug.h>

#include "import.h"

#define PT_PERM_UP 0
#define PT_PERM_PTU (PTE_P | PTE_W | PTE_U)
#define DIR_MASK    0xffc00000

/** ASSIGNMENT INFO:
  * - In this part of the kernel, we will be implementing Virtual Memory Management (VMM) with 
  *   two level paging mechanism.
  * - Like with PMM section, we need certain data structures and abstractions over these structures 
  *   to access and modify them. (See project handout for description of abstraction layers.)
  * - Each abstraction layer is a sub-folder within the vmm folder and is organised the same as 
  *   pmm layer with files export.h, import.h, test.c, <layer_name>.c and the Makefile.inc.
  *
  * HELPFUL LINKS ON PAGING:
  * - Intel 80386 Programmer’s Reference Manual: http://flint.cs.yale.edu/cs422/readings/i386/s05_02.htm
  */ 

/** * VMM Data Structure: PDirPool
  * - We will maintain one page structure for each process.
  * - We will statically allocate page directories, and maintain the second level page tables dynamically.
  * - We have a Page directory pool for NUM_IDS processes.
  *   -- Each PDirPool[index] represents the page directory of the page structure for the process # [index].
  * - We will have a maximum of NUM_IDS (=64) processes. 
  * - The PAGESIZE for VMM is 4096 bytes. 
  * - Each Page Table Entry (pte) is 4 bytes. Therefore, each page can hold 4096/4 = 1024 pte.
  * Page Table Entry Format:
  * 20+9+3=32
  * |31                         12|11          |2   |1   |0  | 
  * |-----------------------------|------------|----|----|---|
  * | Page Frame Address 31..12   |  Flags     |U/S |R/W |P  |
  *
  * - U/S = User / Supervisor bit
  * - R/W = Read / Write bit
  * - P   = Present bit
  */
char * PDirPool[NUM_IDS][1024] gcc_aligned(PAGESIZE);

/** * VMM Data Structure: IDPTbl
  * - In mCertiKOS, we use identity page table mappings for the kernel memory.
  * - IDPTbl is a statically allocated, identity page table that will be reused for
  *   all the kernel memory.
  * - Every page directory entry of kernel memory links to corresponding entry in IDPTbl.
  */
unsigned int IDPTbl[1024][1024] gcc_aligned(PAGESIZE);


/** TASK 1:
  * * Set the CR3 register with the start address of the page structure for process # [index]
  */
void set_pdir_base(unsigned int index)
{
    // TODO
    // dprintf("\nPDirPool[index][0] = %d\n", PDirPool[index]);
    set_cr3((unsigned int)PDirPool[index]);

    // int i;
    // for(i = 0; i < NUM_IDS; i++){
    //   dprintf("i = %d, pde = %u\n", i, (unsigned int)PDirPool[i][300]);
    // }

}

/** TASK 2:
  * * Return the page directory entry # [pde_index] of the process # [proc_index]
  * - This can be used to test whether the page directory entry is mapped
  */
unsigned int get_pdir_entry(unsigned int proc_index, unsigned int pde_index)
{
    // TODO
    return (unsigned int)PDirPool[proc_index][pde_index];
}   

/** TASK 3:
  * * Set specified page directory entry with the start address of physical page # [page_index].
  * - You should also set the permissions PTE_P, PTE_W, and PTE_U
  * Hint 1: PT_PERM_PTU is defined for you.
  * Hint 2: 
  */
void set_pdir_entry(unsigned int proc_index, unsigned int pde_index, unsigned int page_index)
{
    // TODO
    // PDirPool[page_index] = IDPTbl[proc_index][pde_index];
    PDirPool[proc_index][pde_index] = (char*)((page_index<<12) | PT_PERM_PTU);
    // dprintf("\nPDirPool[proc][pde] = %u\n", PDirPool[proc_index][pde_index]);
}   

/** TASK 4:
  * * Set the page directory entry # [pde_index] for the process # [proc_index]
  *   with the initial address of page directory # [pde_index] in IDPTbl
  * - You should also set the permissions PTE_P, PTE_W, and PTE_U
  * - This will be used to map the page directory entry to identity page table.
  * Hint 1: Cast the first entry of IDPTbl[pde_index] to char *.
  */
void set_pdir_entry_identity(unsigned int proc_index, unsigned int pde_index)
{   
    // TODO
    PDirPool[proc_index][pde_index] = (char*)((unsigned int)IDPTbl[pde_index] | PT_PERM_PTU);
    // dprintf("\nIDPTbl[pde_index] = %u\n", (unsigned int)IDPTbl[pde_index] + 7);
    // dprintf("\nval = %u\n", ((unsigned int)IDPTbl[pde_index] | PT_PERM_PTU));
}   

/** TASK 5:
  * * Remove specified page directory entry 
  * Hint 1: Set the page directory entry to PT_PERM_UP.
  * Hint 2: Don't forget to cast the value to (char *).
  */
void rmv_pdir_entry(unsigned int proc_index, unsigned int pde_index)
{
    // TODO
    PDirPool[proc_index][pde_index] = (char*)PT_PERM_UP;
}   

/** TASK 6:
  * * Returns the specified page table entry.
  * Hint 1: Remember that second level page table is dynamically allocated. You cannot simply 
  *         use array indexing as in the first level page table. The offset into the second level
  *         page table can be calculated using: pte_index * size of pte.
  * Hint 2: Do not forget that the permission info is also stored in the page directory entries.
  *         (You will have to mask out the permission info.)
  * Hint 3: Remember to cast to a pointer before de-referencing an address.
  */
unsigned int get_ptbl_entry(unsigned int proc_index, unsigned int pde_index, unsigned int pte_index)
{   
    // TODO
    // dprintf("\nPDir = %u\n", (unsigned int)PDirPool[proc_index][pde_index + pte_index*4]);
    // unsigned int* val;
    // unsigned int frame = (unsigned int)PDirPool[proc_index][pde_index]>>12;
    // frame += 4*pte_index;
    // frame = frame<<12;
    // // frame += 4*pte_index;
    // val = (unsigned int*)frame;

    // // dprintf("\nval = %u\n", *val);
    // // return IDPTbl[pde_index][pte_index] = ;
    // return *val;
    // unsigned int* frame = (unsigned int*)PDirPool[proc_index][pde_index];
    // frame = frame>>12;
    // frame = frame<<12;
    // return frame[pte_index];
    unsigned int* frame;
    unsigned int frameNum = (unsigned int)PDirPool[proc_index][pde_index];
    frameNum = frameNum>>12;
    frameNum = frameNum<<12;
    frame = (unsigned int*)frameNum;
    return frame[pte_index];
}

/** TASK 7:
  * * Sets specified page table entry with the start address of physical page # [page_index]
  * - You should also set the given permission
  * Hint 1: Same as TASK 6
  */
void set_ptbl_entry(unsigned int proc_index, unsigned int pde_index, unsigned int pte_index, unsigned int page_index, unsigned int perm)
{   
    // TODO
    // unsigned int* val;
    // unsigned int frame = (unsigned int)PDirPool[proc_index][pde_index]>>12;
    // frame += 4*pte_index;
    // frame = frame<<12;
    // val = (unsigned int*)frame;
    // *val = page_index<<12 | perm;
    // dprintf("\nval = %u\n", *val);
    // unsigned int* frame = (unsigned int*)PDirPool[proc_index][pde_index];
    // frame = frame>>12;
    // frame = frame<<12;
    // frame[pte_index] = (page_index<<12) | perm;
    unsigned int* frame;
    unsigned int frameNum = (unsigned int)PDirPool[proc_index][pde_index];
    frameNum = frameNum>>12;
    frameNum = frameNum<<12;
    frame = (unsigned int*)frameNum;
    frame[pte_index] = (page_index<<12) | perm;
}   

/** TASK 8:
  * * Set the specified page table entry in IDPTbl as the identity map.
  * - You should also set the given permission
  * Hint 1: Remember that c-language is row-major i.e. for a multi-dimensional array, 
  *         the consecutive elements of a row reside next to each other. 
  * eg. a 2-dimensional array: A[2][3] is stored in memory as follows. 
  *  [https://en.wikipedia.org/wiki/Row-_and_column-major_order]
  * | Address | Array access |
  * |---------|--------------|
  * | 0       |    A[0][0]   |
  * | 1       |    A[0][1]   |       address for A[i][j] is calculated as:
  * | 2       |    A[0][2]   |       addr = (i * num_columns + j) * size_of_each_entry
  * | 3       |    A[1][0]   |       eg. A[1][2] -> (1 * 3 + 2) * 1 = 5
  * | 4       |    A[1][1]   |
  * | 5       |    A[1][2]   |
  * |---------|--------------|
  */
void set_ptbl_entry_identity(unsigned int pde_index, unsigned int pte_index, unsigned int perm)
{
    // TODO
    // IDPTbl[pde_index][pte_index] = ((pde_index*1024 + pte_index)*4096) | perm;
    // IDPTbl[pde_index][pte_index] = pde_index*1024*4096 | perm;
    // dprintf("perm = %u\n", perm);
    // IDPTbl[pde_index][pte_index] = pde_index*1024*4096 + perm;
    // dprintf("\nidptbl[0] addr = %u\n", (unsigned int)IDPTbl[0]);
    IDPTbl[pde_index][pte_index] = (pde_index*1024 + pte_index)*4096 | perm;
}

/** TASK 9:
  * * Set the specified page table entry to 0
  * Hint 1: Remember that page directory entries also have permissions stored. Mask them out.
  * Hint 2: Remember to cast to a pointer before de-referencing an address.
  */
void rmv_ptbl_entry(unsigned int proc_index, unsigned int pde_index, unsigned int pte_index)
{
    // TODO
    // unsigned int* val;
    // unsigned int frame = (unsigned int)PDirPool[proc_index][pde_index]>>12;
    // frame += 4*pte_index;
    // frame = frame<<12;
    // val = (unsigned int*)frame;
    // *val = 0;
    unsigned int* frame;
    unsigned int frameNum = (unsigned int)PDirPool[proc_index][pde_index];
    frameNum = frameNum>>12;
    frameNum = frameNum<<12;
    frame = (unsigned int*)frameNum;
    frame[pte_index] = 0;
}
