/* atm.h - general ATM declarations */
#ifndef _BEEP_ATM_H
#define _BEEP_ATM_H

#include <uapi/beep/atm.h>

#ifdef CONFIG_COMPAT
#include <beep/compat.h>
struct compat_atmif_sioc {
	int number;
	int length;
	compat_uptr_t arg;
};
#endif
#endif
