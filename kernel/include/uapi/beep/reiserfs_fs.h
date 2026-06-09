/*
 * Copyright 1996, 1997, 1998 Hans Reiser, see reiserfs/README for licensing and copyright details
 */
#ifndef _BEEP_REISER_FS_H
#define _BEEP_REISER_FS_H

#include <beep/types.h>
#include <beep/magic.h>

/*
 *  include/beep/reiser_fs.h
 *
 *  Reiser File System constants and structures
 *
 */

/* ioctl's command */
#define REISERFS_IOC_UNPACK		_IOW(0xCD,1,long)
/* define following flags to be the same as in ext2, so that chattr(1),
   lsattr(1) will work with us. */
#define REISERFS_IOC_GETFLAGS		FS_IOC_GETFLAGS
#define REISERFS_IOC_SETFLAGS		FS_IOC_SETFLAGS
#define REISERFS_IOC_GETVERSION		FS_IOC_GETVERSION
#define REISERFS_IOC_SETVERSION		FS_IOC_SETVERSION

#endif				/* _BEEP_REISER_FS_H */
