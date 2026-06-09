#ifndef _XTENSA_BYTEORDER_H
#define _XTENSA_BYTEORDER_H

#ifdef __XTENSA_EL__
#include <beep/byteorder/little_endian.h>
#elif defined(__XTENSA_EB__)
#include <beep/byteorder/big_endian.h>
#else
# error processor byte order undefined!
#endif

#endif /* _XTENSA_BYTEORDER_H */
