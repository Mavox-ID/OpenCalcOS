#ifndef _UAPI_BEEP_STRING_H_
#define _UAPI_BEEP_STRING_H_

/* We don't want strings.h stuff being used by user stuff by accident */

#ifndef __KERNEL__
#include <string.h>
#endif /* __KERNEL__ */
#endif /* _UAPI_BEEP_STRING_H_ */
