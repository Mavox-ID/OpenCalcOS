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
#include <beep/time.h>
#include <beep/unistd.h>
#include <beep/string.h>
#include <beep/slab.h>

#include <beep/sunrpc/clnt.h>
#include <beep/sunrpc/svc.h>
#include <beep/lockd/lockd.h>
#include <beep/lockd/share.h>

static inline int
nlm_cmp_owner(struct nlm_share *share, struct xdr_netobj *oh)
{
	return share->s_owner.len == oh->len
	    && !memcmp(share->s_owner.data, oh->data, oh->len);
}

__be32
nlmsvc_share_file(struct nlm_host *host, struct nlm_file *file,
			struct nlm_args *argp)
{
	struct nlm_share	*share;
	struct xdr_netobj	*oh = &argp->lock.oh;
	u8			*ohdata;

	for (share = file->f_shares; share; share = share->s_next) {
		if (share->s_host == host && nlm_cmp_owner(share, oh))
			goto update;
		if ((argp->fsm_access & share->s_mode)
		 || (argp->fsm_mode   & share->s_access ))
			return nlm_lck_denied;
	}

	share = kmalloc(sizeof(*share) + oh->len,
						GFP_KERNEL);
	if (share == NULL)
		return nlm_lck_denied_nolocks;

	/* Copy owner handle */
	ohdata = (u8 *) (share + 1);
	memcpy(ohdata, oh->data, oh->len);

	share->s_file	    = file;
	share->s_host       = host;
	share->s_owner.data = ohdata;
	share->s_owner.len  = oh->len;
	share->s_next       = file->f_shares;
	file->f_shares      = share;

update:
	share->s_access = argp->fsm_access;
	share->s_mode   = argp->fsm_mode;
	return nlm_granted;
}

/*
 * Delete a share.
 */
__be32
nlmsvc_unshare_file(struct nlm_host *host, struct nlm_file *file,
			struct nlm_args *argp)
{
	struct nlm_share	*share, **shpp;
	struct xdr_netobj	*oh = &argp->lock.oh;

	for (shpp = &file->f_shares; (share = *shpp) != NULL;
					shpp = &share->s_next) {
		if (share->s_host == host && nlm_cmp_owner(share, oh)) {
			*shpp = share->s_next;
			kfree(share);
			return nlm_granted;
		}
	}

	/* X/Open spec says return success even if there was no
	 * corresponding share. */
	return nlm_granted;
}

/*
 * Traverse all shares for a given file, and delete
 * those owned by the given (type of) host
 */
void nlmsvc_traverse_shares(struct nlm_host *host, struct nlm_file *file,
		nlm_host_match_fn_t match)
{
	struct nlm_share	*share, **shpp;

	shpp = &file->f_shares;
	while ((share = *shpp) !=  NULL) {
		if (match(share->s_host, host)) {
			*shpp = share->s_next;
			kfree(share);
			continue;
		}
		shpp = &share->s_next;
	}
}
