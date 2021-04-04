#ifndef _KERN_DPRINTF_H_
#define _KERN_DRPINTF_H_

#ifdef _KERN_
#include "stdarg.h"

int vdprintf (const char *fmt, va_list ap);

#endif /* _KERN_ */

#endif /* !_KERN_DRPINTF_H_ */
