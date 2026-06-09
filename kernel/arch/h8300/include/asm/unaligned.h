#ifndef _ASM_H8300_UNALIGNED_H
#define _ASM_H8300_UNALIGNED_H

#include <beep/unaligned/be_memmove.h>
#include <beep/unaligned/le_byteshift.h>
#include <beep/unaligned/generic.h>

#define get_unaligned	__get_unaligned_be
#define put_unaligned	__put_unaligned_be

#endif /* _ASM_H8300_UNALIGNED_H */
