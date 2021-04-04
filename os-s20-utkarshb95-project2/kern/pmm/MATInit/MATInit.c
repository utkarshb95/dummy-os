#include <lib/debug.h>
#include "import.h"

#define PAGESIZE	4096
#define VM_USERLO	0x40000000
#define VM_USERHI	0xF0000000
#define VM_USERLO_PI	(VM_USERLO / PAGESIZE)   // VM_USERLO page index
#define VM_USERHI_PI	(VM_USERHI / PAGESIZE)   // VM_USERHI page index

#define TRUE 1
#define FALSE 0


void
pmem_init(unsigned int mbi_addr)
{
  unsigned int nps;

  // TODO: Define your local variables here.
  unsigned int numRows, lastAddr, i, row, start, stop, addrStart, addrStop;
  char found;

 
	devinit(mbi_addr);


  
  // TODO
  numRows = get_size();
  lastAddr = get_mms(numRows - 1) + get_mml(numRows - 1);
  nps = lastAddr / PAGESIZE + 1;

	set_nps(nps); // Setting the value computed above to NUM_PAGES.


  for(i = 0; i < nps; i++){
    // Kernel pages
    if(i < VM_USERLO_PI || i >= VM_USERHI_PI)
      at_set_perm(i, 1);
    
    // Checks non-kernel pages
    else {
      // Gets start and end address for page, sets found to false
      addrStart = i*PAGESIZE;
      addrStop = addrStart + PAGESIZE - 1;
      found = FALSE;

      // Checks mem map row by row
      for(row = 0; row < numRows; row++){
        // Gets row start and stop addresses
        start = get_mms(row);
        stop = start + get_mml(row);

        // Checks 
        if(addrStart >= start && addrStop < stop){
          if(is_usable(row))
            at_set_perm(i, 2);
          else
            at_set_perm(i, 0);
          found = TRUE;
          break;
        }
      }
      if(found == FALSE)
        at_set_perm(i, 0);
    }
  }

}