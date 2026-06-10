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
#include <beep/nfs_fs.h>
#include "nfs4_fs.h"
#include "internal.h"

#define NFSDBG_FACILITY		NFSDBG_CLIENT

int nfs4_get_rootfh(struct nfs_server *server, struct nfs_fh *mntfh)
{
	struct nfs_fsinfo fsinfo;
	int ret = -ENOMEM;

	dprintk("--> nfs4_get_rootfh()\n");

	fsinfo.fattr = nfs_alloc_fattr();
	if (fsinfo.fattr == NULL)
		goto out;

	/* Start by getting the root filehandle from the server */
	ret = nfs4_proc_get_rootfh(server, mntfh, &fsinfo);
	if (ret < 0) {
		dprintk("nfs4_get_rootfh: getroot error = %d\n", -ret);
		goto out;
	}

	if (!(fsinfo.fattr->valid & NFS_ATTR_FATTR_TYPE)
			|| !S_ISDIR(fsinfo.fattr->mode)) {
		printk(KERN_ERR "nfs4_get_rootfh:"
		       " getroot encountered non-directory\n");
		ret = -ENOTDIR;
		goto out;
	}

	if (fsinfo.fattr->valid & NFS_ATTR_FATTR_V4_REFERRAL) {
		printk(KERN_ERR "nfs4_get_rootfh:"
		       " getroot obtained referral\n");
		ret = -EREMOTE;
		goto out;
	}

	memcpy(&server->fsid, &fsinfo.fattr->fsid, sizeof(server->fsid));
out:
	nfs_free_fattr(fsinfo.fattr);
	dprintk("<-- nfs4_get_rootfh() = %d\n", ret);
	return ret;
}
