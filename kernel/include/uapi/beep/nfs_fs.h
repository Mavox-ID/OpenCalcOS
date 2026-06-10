/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _UAPI_BEEP_NFS_FS_H
#define _UAPI_BEEP_NFS_FS_H

#include <beep/magic.h>

/* Default timeout values */
#define NFS_DEF_UDP_TIMEO	(11)
#define NFS_DEF_UDP_RETRANS	(3)
#define NFS_DEF_TCP_TIMEO	(600)
#define NFS_DEF_TCP_RETRANS	(2)

#define NFS_MAX_UDP_TIMEOUT	(60*HZ)
#define NFS_MAX_TCP_TIMEOUT	(600*HZ)

#define NFS_DEF_ACREGMIN	(3)
#define NFS_DEF_ACREGMAX	(60)
#define NFS_DEF_ACDIRMIN	(30)
#define NFS_DEF_ACDIRMAX	(60)

/*
 * When flushing a cluster of dirty pages, there can be different
 * strategies:
 */
#define FLUSH_SYNC		1	/* file being synced, or contention */
#define FLUSH_STABLE		4	/* commit to stable storage */
#define FLUSH_LOWPRI		8	/* low priority background flush */
#define FLUSH_HIGHPRI		16	/* high priority memory reclaim flush */
#define FLUSH_COND_STABLE	32	/* conditional stable write - only stable
					 * if everything fits in one RPC */


/*
 * NFS debug flags
 */
#define NFSDBG_VFS		0x0001
#define NFSDBG_DIRCACHE		0x0002
#define NFSDBG_LOOKUPCACHE	0x0004
#define NFSDBG_PAGECACHE	0x0008
#define NFSDBG_PROC		0x0010
#define NFSDBG_XDR		0x0020
#define NFSDBG_FILE		0x0040
#define NFSDBG_ROOT		0x0080
#define NFSDBG_CALLBACK		0x0100
#define NFSDBG_CLIENT		0x0200
#define NFSDBG_MOUNT		0x0400
#define NFSDBG_FSCACHE		0x0800
#define NFSDBG_PNFS		0x1000
#define NFSDBG_PNFS_LD		0x2000
#define NFSDBG_STATE		0x4000
#define NFSDBG_ALL		0xFFFF


#endif /* _UAPI_BEEP_NFS_FS_H */
