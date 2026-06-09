#ifndef _BEEP_START_KERNEL_H
#define _BEEP_START_KERNEL_H

#include <beep/linkage.h>
#include <beep/init.h>

/* Define the prototype for start_kernel here, rather than cluttering
   up something else. */

extern asmlinkage void __init start_kernel(void);

#endif /* _BEEP_START_KERNEL_H */
