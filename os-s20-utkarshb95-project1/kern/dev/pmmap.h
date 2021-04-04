#include <lib/queue.h>

struct pmmap {
	uintptr_t		start;
	uintptr_t		end;
	uint32_t		type;
	SLIST_ENTRY(pmmap)	next;
	SLIST_ENTRY(pmmap)	type_next;
};

typedef SLIST_HEAD(, pmmap) pmmap_list_type;