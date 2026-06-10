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
#include <beep/file.h>
#include <beep/lockd/bind.h>
#include "nfsd.h"
#include "vfs.h"

#define NFSDDBG_FACILITY		NFSDDBG_LOCKD

#ifdef CONFIG_LOCKD_V4
#define nlm_stale_fh	nlm4_stale_fh
#define nlm_failed	nlm4_failed
#else
#define nlm_stale_fh	nlm_lck_denied_nolocks
#define nlm_failed	nlm_lck_denied_nolocks
#endif
/*
 * Note: we hold the dentry use count while the file is open.
 */
static __be32
nlm_fopen(struct svc_rqst *rqstp, struct nfs_fh *f, struct file **filp)
{
	__be32		nfserr;
	struct svc_fh	fh;

	/* must initialize before using! but maxsize doesn't matter */
	fh_init(&fh,0);
	fh.fh_handle.fh_size = f->size;
	memcpy((char*)&fh.fh_handle.fh_base, f->data, f->size);
	fh.fh_export = NULL;

	nfserr = nfsd_open(rqstp, &fh, S_IFREG, NFSD_MAY_LOCK, filp);
	fh_put(&fh);
 	/* We return nlm error codes as nlm doesn't know
	 * about nfsd, but nfsd does know about nlm..
	 */
	switch (nfserr) {
	case nfs_ok:
		return 0;
	case nfserr_dropit:
		return nlm_drop_reply;
	case nfserr_stale:
		return nlm_stale_fh;
	default:
		return nlm_failed;
	}
}

static void
nlm_fclose(struct file *filp)
{
	fput(filp);
}

static struct nlmsvc_binding	nfsd_nlm_ops = {
	.fopen		= nlm_fopen,		/* open file for locking */
	.fclose		= nlm_fclose,		/* close file */
};

void
nfsd_lockd_init(void)
{
	dprintk("nfsd: initializing lockd\n");
	nlmsvc_ops = &nfsd_nlm_ops;
}

void
nfsd_lockd_shutdown(void)
{
	nlmsvc_ops = NULL;
}
