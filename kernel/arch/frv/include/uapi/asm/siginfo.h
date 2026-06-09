#ifndef _ASM_SIGINFO_H
#define _ASM_SIGINFO_H

#include <beep/types.h>
#include <asm-generic/siginfo.h>

#define FPE_MDAOVF	(__SI_FAULT|9)	/* media overflow */
#undef NSIGFPE
#define NSIGFPE		9

#endif

