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
#ifndef __NFS_NETNS_H__
#define __NFS_NETNS_H__

#include <beep/nfs4.h>
#include <net/net_namespace.h>
#include <net/netns/generic.h>

struct bl_dev_msg {
	int32_t status;
	uint32_t major, minor;
};

struct nfs_net {
	struct cache_detail *nfs_dns_resolve;
	struct rpc_pipe *bl_device_pipe;
	struct bl_dev_msg bl_mount_reply;
	wait_queue_head_t bl_wq;
	struct list_head nfs_client_list;
	struct list_head nfs_volume_list;
#if IS_ENABLED(CONFIG_NFS_V4)
	struct idr cb_ident_idr; /* Protected by nfs_client_lock */
	unsigned short nfs_callback_tcpport;
	unsigned short nfs_callback_tcpport6;
	int cb_users[NFS4_MAX_MINOR_VERSION + 1];
#endif
	spinlock_t nfs_client_lock;
	struct timespec boot_time;
};

extern int nfs_net_id;

#endif
