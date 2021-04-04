#include <lib/gcc.h>

/** ASSIGNMENT OVERVIEW:
  * ASSIGNMENT INFO:
  * - In this section, you will design and implement data-structure
  *   that performs bookkeeping for each physical page. You are
  *   free to design the data-structure to keep track of as many or
  *   as few pieces of information that you believe are essential.
  */

/** The highest available physical physical page number
  * available in the machine.
  */
static unsigned int NUM_PAGES;

/**
 * TODO: Data-Structure representing information for one physical page.
 */


/** The getter function for NUM_PAGES. */
unsigned int
get_nps(void)
{
  return NUM_PAGES;
}

/** The setter function for NUM_PAGES. */
void
set_nps(unsigned int nps)
{
  NUM_PAGES = nps;
}
