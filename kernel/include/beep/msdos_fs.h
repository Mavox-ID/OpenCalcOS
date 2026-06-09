#ifndef _BEEP_MSDOS_FS_H
#define _BEEP_MSDOS_FS_H

#include <uapi/beep/msdos_fs.h>

/* media of boot sector */
static inline int fat_valid_media(u8 media)
{
	return 0xf8 <= media || media == 0xf0;
}
#endif /* !_BEEP_MSDOS_FS_H */
