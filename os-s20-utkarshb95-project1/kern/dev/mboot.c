#include <lib/debug.h>
#include <lib/x86.h>
#include <lib/gcc.h>
#include <lib/queue.h>
#include <lib/types.h>

#include "mboot.h"


static int pmmap_slots_next_free = 0;
static struct pmmap pmmap_slots[128];
//static SLIST_HEAD(, pmmap) pmmap_list;	/* all memory regions */
static SLIST_HEAD(, pmmap) pmmap_sublist[4];

enum __pmmap_type { PMMAP_USABLE, PMMAP_RESV, PMMAP_ACPI, PMMAP_NVS };

#define PMMAP_SUBLIST_NR(type)				\
	(((type) == MEM_RAM) ? PMMAP_USABLE :		\
	 ((type) == MEM_RESERVED) ? PMMAP_RESV :	\
	 ((type) == MEM_ACPI) ? PMMAP_ACPI :		\
	 ((type) == MEM_NVS) ? PMMAP_NVS : -1)

struct pmmap *
pmmap_alloc_slot(void)
{
	if (unlikely(pmmap_slots_next_free == 128))
		return NULL;
	return &pmmap_slots[pmmap_slots_next_free++];
}

/*
 * Insert an physical memory map entry in pmmap[].
 *
 * XXX: The start fields of all entries of the physical memory map are in
 *      incremental order.
 * XXX: The memory regions of some entries maybe overlapped.
 *
 * @param start
 * @param end
 * @param type
 */
static void
pmmap_insert(pmmap_list_type *pmmap_list_p, uintptr_t start, uintptr_t end, uint32_t type)
{
	struct pmmap *free_slot, *slot, *last_slot;

	if ((free_slot = pmmap_alloc_slot()) == NULL)
		KERN_PANIC("More than 128 E820 entries.\n");

	free_slot->start = start;
	free_slot->end = end;
	free_slot->type = type;

	last_slot = NULL;

	SLIST_FOREACH(slot, pmmap_list_p, next) {
		if (start < slot->start)
			break;
		last_slot = slot;
	}

	if (last_slot == NULL)
  {
		SLIST_INSERT_HEAD(pmmap_list_p, free_slot, next);
  }
	else
  {
		SLIST_INSERT_AFTER(last_slot, free_slot, next);
  }
}

static void
pmmap_merge(pmmap_list_type *pmmap_list_p)
{
	struct pmmap *slot, *next_slot;
	struct pmmap *last_slot[4] = { NULL, NULL, NULL, NULL };
	int sublist_nr;

	/*
	 * Step 1: Merge overlaped entries in pmmap_list.
	 */
	SLIST_FOREACH(slot, pmmap_list_p, next) {
		if ((next_slot = SLIST_NEXT(slot, next)) == NULL)
			break;
		if (slot->start <= next_slot->start &&
		    slot->end >= next_slot->start &&
		    slot->type == next_slot->type) {
			slot->end = max(slot->end, next_slot->end);
			SLIST_REMOVE_AFTER(slot, next);
		}
	}

	/*
	 * Step 2: Create the specfic lists: pmmap_usable, pmmap_resv,
	 *         pmmap_acpi, pmmap_nvs.
	 */
	SLIST_FOREACH(slot, pmmap_list_p, next) {
		sublist_nr = PMMAP_SUBLIST_NR(slot->type); //get memory type number
    	KERN_ASSERT(sublist_nr != -1);
		if (last_slot[sublist_nr] != NULL)
			SLIST_INSERT_AFTER(last_slot[sublist_nr], slot,
					   type_next);
		else
			SLIST_INSERT_HEAD(&pmmap_sublist[sublist_nr], slot,
					  type_next);
		last_slot[sublist_nr] = slot;
	}

}

static void
pmmap_dump(pmmap_list_type *pmmap_list_p)
{
	struct pmmap *slot;
	SLIST_FOREACH(slot, pmmap_list_p, next) {
		KERN_INFO("BIOS-e820: 0x%08x - 0x%08x (%s)\n",
			  slot->start,
			  (slot->start == slot->end) ? slot->end :
			  (slot->end == 0xffffffff) ? slot->end : slot->end - 1,
			  (slot->type == MEM_RAM) ? "usable" :
			  (slot->type == MEM_RESERVED) ? "reserved" :
			  (slot->type == MEM_ACPI) ? "ACPI data" :
			  (slot->type == MEM_NVS) ? "ACPI NVS" :
			  "unknown");
	}
}

void
pmmap_init(uintptr_t mbi_addr, pmmap_list_type *pmmap_list_p)
{
	KERN_INFO("\n");
	KERN_DEBUG("pmmap_init mbi_adr: %d\n", mbi_addr);

	mboot_info_t *mbi = (mboot_info_t *) mbi_addr;
	mboot_mmap_t *p = (mboot_mmap_t *) mbi->mmap_addr;

	SLIST_INIT(pmmap_list_p);
	SLIST_INIT(&pmmap_sublist[PMMAP_USABLE]);
	SLIST_INIT(&pmmap_sublist[PMMAP_RESV]);
	SLIST_INIT(&pmmap_sublist[PMMAP_ACPI]);
	SLIST_INIT(&pmmap_sublist[PMMAP_NVS]);

	/*
	 * Copy memory map information from multiboot information mbi to pmmap.
	 */
	while ((uintptr_t) p - (uintptr_t) mbi->mmap_addr < mbi->mmap_length) {
		uintptr_t start,end;
		uint32_t type;

		if (p->base_addr_high != 0)	/* ignore address above 4G */
			goto next;
		else
			start = p->base_addr_low;

		if (p->length_high != 0 ||
		    p->length_low >= 0xffffffff - start)
			end = 0xffffffff;
		else
			end = start + p->length_low;

		type = p->type;

		pmmap_insert(pmmap_list_p, start, end, type);

		next:
			p = (mboot_mmap_t *) (((uint32_t) p) + sizeof(mboot_mmap_t)/* p->size */);
	}

	/* merge overlapped memory regions */
	pmmap_merge(pmmap_list_p);
}


void
set_cr3(char **pdir)
{
	lcr3((uint32_t) pdir);
}

/** Task 1:
  * Enable paging
  *
  * This function enables paging in the hardware by updating the control
  * registers.
  *
  * - First we set the Page Global Enable (CR4_PGE) bit of the CR4 register.
  *
  * - Then set the Monitor co-processor, extension type, numeric error,
  *   write protect, and alignment mask bits in the CR0 register in addition
  *   to the protected mode enable and paging bits.
  *
  * Hint: bit masks are defined in x86.h file.
  */
void
enable_paging(void)
{
    //TODO
}
