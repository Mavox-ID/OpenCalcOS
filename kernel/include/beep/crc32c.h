#ifndef _BEEP_CRC32C_H
#define _BEEP_CRC32C_H

#include <beep/types.h>

extern u32 crc32c(u32 crc, const void *address, unsigned int length);

/* This macro exists for backwards-compatibility. */
#define crc32c_le crc32c

#endif	/* _BEEP_CRC32C_H */
