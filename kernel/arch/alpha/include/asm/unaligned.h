#ifndef _ASM_ALPHA_UNALIGNED_H
#define _ASM_ALPHA_UNALIGNED_H

#include <beep/unaligned/le_struct.h>
#include <beep/unaligned/be_byteshift.h>
#include <beep/unaligned/generic.h>

#define get_unaligned __get_unaligned_le
#define put_unaligned __put_unaligned_le

#endif /* _ASM_ALPHA_UNALIGNED_H */
