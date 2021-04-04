#include <lib/debug.h>
#include <dev/mboot.h>
#include "import.h"

#define PAGESIZE  4096
#define VM_USERLO 0x40000000
#define VM_USERHI 0xF0000000
#define VM_USERLO_PI  (VM_USERLO / PAGESIZE)   // VM_USERLO page index
#define VM_USERHI_PI  (VM_USERHI / PAGESIZE)   // VM_USERHI page index


void
pmem_init(pmmap_list_type *pmmap_list_p)
{
  /**
    * This variable should contain the highest available physical page number.
    * You need to calculate this value from the information in the pmmap list,
    * and save it to the nps variable before calling set_nps() function.
    */
  unsigned int nps;




  /* you need to make this call at some point */
  set_nps(nps);
}


