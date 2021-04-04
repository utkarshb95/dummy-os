#include <lib/debug.h>
#include <pmm/MATIntro/export.h>
#include "export.h"

int test_allocation(int page_index) {
  if (page_index < 262144) {
    pfree(page_index);
    dprintf("test 1-a failed with page_index = %d.\n", page_index);
    return 1;
  }
  if (at_is_norm(page_index) != 1) {
    pfree(page_index);
    dprintf("test 1-b failed.\n");
    return 1;
  }
  if (at_is_allocated(page_index) != 1) {
    pfree(page_index);
    dprintf("test 1-c failed.\n");
    return 1;
  }
  return 0;
}

int test_free(int page_index) {
  pfree(page_index);
  if (at_is_allocated(page_index) != 0) {
    dprintf("test 1-d failed.\n");
    return 1;
  }
  return 0; 
}

int MATOp_test1()
{
  int page_index = palloc();
  if (test_allocation(page_index) == 1) return 1;
  if (test_free(page_index) == 1) return 1;
  dprintf("test 1 passed.\n");
  return 0;
}

/**
 * Write Your Own Test Script (optional)
 *
 * Come up with your own interesting test cases to challenge your classmates!
 * In addition to the provided simple tests, selected (correct and interesting) test functions
 * will be used in the actual grading of the lab!
 * Your test function itself will not be graded. So don't be afraid of submitting a wrong script.
 *
 * The test function should return 0 for passing the test and a non-zero code for failing the test.
 * Be extra careful to make sure that if you overwrite some of the kernel data, they are set back to
 * the original value. O.w., it may make the future test scripts to fail even if you implement all
 * the functions correctly.
 */
int MATOp_test_own()
{
  // TODO (optional)
  int page_index = palloc();
  int next_page_index;
  int max_available_pages = get_nps() - 262144;
  for (int i = 0; i < max_available_pages + 10; i++) {
    next_page_index = palloc();
    if (test_allocation(page_index) == 1){
      dprintf("Own allocation test: Failed on iteration: %d\n", i); 
      return 1;
    }
    if (test_free(page_index) == 1) {
      dprintf("Own free test: Failed on iteration: %d\n", i);
      return 1;
    }
    page_index = next_page_index;
  }
  pfree(page_index);
  dprintf("page_index is: %d\n", page_index);

  dprintf("own test passed.\n");
  return 0;
}

int test_MATOp()
{
  return MATOp_test1() + MATOp_test_own();
}
