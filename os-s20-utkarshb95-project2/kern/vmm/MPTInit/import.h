#ifndef _KERN_MM_MPTINIT_H_
#define _KERN_MM_MPTINIT_H_

#ifdef _KERN_

void pdir_init_kern(unsigned int);
void set_pdir_base(unsigned int);
void enable_paging(void);

#endif /* _KERN_ */

#endif /* !_KERN_MM_MPTINIT_H_ */
