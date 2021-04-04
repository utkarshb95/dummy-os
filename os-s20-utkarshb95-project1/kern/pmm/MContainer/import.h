#ifndef _KERN_MM_MCONTAINER_H_
#define _KERN_MM_MCONTAINER_H_

#ifdef _KERN_

unsigned int get_nps(void);
unsigned int palloc(void);
void pfree(unsigned int);

#endif /* _KERN_ */

#endif /* !_KERN_MM_MCONTAINER_H_ */
