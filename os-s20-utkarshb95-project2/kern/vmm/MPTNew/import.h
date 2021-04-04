#ifndef _KERN_MM_MPTNEW_H_
#define _KERN_MM_MPTNEW_H_

#ifdef _KERN_

unsigned int container_alloc(unsigned int);
unsigned int container_split(unsigned int, unsigned int);
unsigned int map_page(unsigned int, unsigned int, unsigned int, unsigned int);

#endif /* _KERN_ */

#endif /* !_KERN_MM_MPTNEW_H_ */
