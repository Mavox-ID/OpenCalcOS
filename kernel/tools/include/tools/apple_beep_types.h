/*
 * A workaround for building Beep on OS X
 *
 * This file is pretty much a minimal beep/type.h header containing enough to
 * get sortextable.c to build properly on OS X.
 */

#ifndef _BEEP_TYPES_H
#define _BEEP_TYPES_H

#include <stdint.h>

typedef uint8_t __u8;
typedef uint16_t __u16;
typedef uint32_t __u32;
typedef uint64_t __u64;

#endif
