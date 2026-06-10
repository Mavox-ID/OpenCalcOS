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
#include <beep/mm.h>
#include <beep/pagemap.h>
#include <beep/sunrpc/sched.h>
#include <beep/sunrpc/clnt.h>

#include <beep/nfs.h>
#include <beep/nfs4.h>
#include <beep/nfs_fs.h>
#include "nfs4_fs.h"
#include "delegation.h"

#define NFSDBG_FACILITY		NFSDBG_STATE

void
nfs4_renew_state(struct work_struct *work)
{
	const struct nfs4_state_maintenance_ops *ops;
	struct nfs_client *clp =
		container_of(work, struct nfs_client, cl_renewd.work);
	struct rpc_cred *cred;
	long lease;
	unsigned long last, now;
	unsigned renew_flags = 0;

	ops = clp->cl_mvops->state_renewal_ops;
	dprintk("%s: start\n", __func__);

	if (test_bit(NFS_CS_STOP_RENEW, &clp->cl_res_state))
		goto out;

	spin_lock(&clp->cl_lock);
	lease = clp->cl_lease_time;
	last = clp->cl_last_renewal;
	now = jiffies;
	/* Are we close to a lease timeout? */
	if (time_after(now, last + lease/3))
		renew_flags |= NFS4_RENEW_TIMEOUT;
	if (nfs_delegations_present(clp))
		renew_flags |= NFS4_RENEW_DELEGATION_CB;

	if (renew_flags != 0) {
		cred = ops->get_state_renewal_cred_locked(clp);
		spin_unlock(&clp->cl_lock);
		if (cred == NULL) {
			if (!(renew_flags & NFS4_RENEW_DELEGATION_CB)) {
				set_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state);
				goto out;
			}
			nfs_expire_all_delegations(clp);
		} else {
			/* Queue an asynchronous RENEW. */
			ops->sched_state_renewal(clp, cred, renew_flags);
			put_rpccred(cred);
			goto out_exp;
		}
	} else {
		dprintk("%s: failed to call renewd. Reason: lease not expired \n",
				__func__);
		spin_unlock(&clp->cl_lock);
	}
	nfs4_schedule_state_renewal(clp);
out_exp:
	nfs_expire_unreferenced_delegations(clp);
out:
	dprintk("%s: done\n", __func__);
}

void
nfs4_schedule_state_renewal(struct nfs_client *clp)
{
	long timeout;

	spin_lock(&clp->cl_lock);
	timeout = (2 * clp->cl_lease_time) / 3 + (long)clp->cl_last_renewal
		- (long)jiffies;
	if (timeout < 5 * HZ)
		timeout = 5 * HZ;
	dprintk("%s: requeueing work. Lease period = %ld\n",
			__func__, (timeout + HZ - 1) / HZ);
	mod_delayed_work(system_wq, &clp->cl_renewd, timeout);
	set_bit(NFS_CS_RENEWD, &clp->cl_res_state);
	spin_unlock(&clp->cl_lock);
}

void
nfs4_kill_renewd(struct nfs_client *clp)
{
	cancel_delayed_work_sync(&clp->cl_renewd);
}

/*
 * Local variables:
 *   c-basic-offset: 8
 * End:
 */
