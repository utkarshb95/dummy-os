#include <lib/x86.h>
#include <lib/types.h>
#include <lib/debug.h>
#include <lib/seg.h>

#include "console.h"
#include "mboot.h"

void intr_init(void);

void
devinit (void)
{
	seg_init ();

	cons_init ();
	KERN_DEBUG("cons initialized.\n");

	intr_init();
}
