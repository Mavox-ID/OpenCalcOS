#ifndef _ASM_PARISC_UNALIGNED_H
#define _ASM_PARISC_UNALIGNED_H

#include <beep/unaligned/be_struct.h>
#include <beep/unaligned/le_byteshift.h>
#include <beep/unaligned/generic.h>
#define get_unaligned	__get_unaligned_be
#define put_unaligned	__put_unaligned_be

#ifdef __KERNEL__
struct pt_regs;
void handle_unaligned(struct pt_regs *regs);
int check_unaligned(struct pt_regs *regs);
#endif

#endif /* _ASM_PARISC_UNALIGNED_H */
