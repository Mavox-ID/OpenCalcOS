#ifndef _BEEP_SECUREBITS_H
#define _BEEP_SECUREBITS_H 1

#include <uapi/beep/securebits.h>

#define issecure(X)		(issecure_mask(X) & current_cred_xxx(securebits))
#endif /* !_BEEP_SECUREBITS_H */
