#ifndef __ALPHA_COMPILER_H
#define __ALPHA_COMPILER_H

#include <uapi/asm/compiler.h>

/* Some idiots over in <beep/compiler.h> thought inline should imply
   always_inline.  This breaks stuff.  We'll include this file whenever
   we run into such problems.  */

#include <beep/compiler.h>
#undef inline
#undef __inline__
#undef __inline
#undef __always_inline
#define __always_inline		inline __attribute__((always_inline))

#endif /* __ALPHA_COMPILER_H */
