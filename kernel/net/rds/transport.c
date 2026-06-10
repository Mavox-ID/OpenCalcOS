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
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/in.h>

#include "rds.h"
#include "loop.h"

static struct rds_transport *transports[RDS_TRANS_COUNT];
static DECLARE_RWSEM(rds_trans_sem);

int rds_trans_register(struct rds_transport *trans)
{
	BUG_ON(strlen(trans->t_name) + 1 > TRANSNAMSIZ);

	down_write(&rds_trans_sem);

	if (transports[trans->t_type])
		printk(KERN_ERR "RDS Transport type %d already registered\n",
			trans->t_type);
	else {
		transports[trans->t_type] = trans;
		printk(KERN_INFO "Registered RDS/%s transport\n", trans->t_name);
	}

	up_write(&rds_trans_sem);

	return 0;
}
EXPORT_SYMBOL_GPL(rds_trans_register);

void rds_trans_unregister(struct rds_transport *trans)
{
	down_write(&rds_trans_sem);

	transports[trans->t_type] = NULL;
	printk(KERN_INFO "Unregistered RDS/%s transport\n", trans->t_name);

	up_write(&rds_trans_sem);
}
EXPORT_SYMBOL_GPL(rds_trans_unregister);

void rds_trans_put(struct rds_transport *trans)
{
	if (trans && trans->t_owner)
		module_put(trans->t_owner);
}

struct rds_transport *rds_trans_get_preferred(__be32 addr)
{
	struct rds_transport *ret = NULL;
	struct rds_transport *trans;
	unsigned int i;

	if (IN_LOOPBACK(ntohl(addr)))
		return &rds_loop_transport;

	down_read(&rds_trans_sem);
	for (i = 0; i < RDS_TRANS_COUNT; i++) {
		trans = transports[i];

		if (trans && (trans->laddr_check(addr) == 0) &&
		    (!trans->t_owner || try_module_get(trans->t_owner))) {
			ret = trans;
			break;
		}
	}
	up_read(&rds_trans_sem);

	return ret;
}

/*
 * This returns the number of stats entries in the snapshot and only
 * copies them using the iter if there is enough space for them.  The
 * caller passes in the global stats so that we can size and copy while
 * holding the lock.
 */
unsigned int rds_trans_stats_info_copy(struct rds_info_iterator *iter,
				       unsigned int avail)

{
	struct rds_transport *trans;
	unsigned int total = 0;
	unsigned int part;
	int i;

	rds_info_iter_unmap(iter);
	down_read(&rds_trans_sem);

	for (i = 0; i < RDS_TRANS_COUNT; i++)
	{
		trans = transports[i];
		if (!trans || !trans->stats_info_copy)
			continue;

		part = trans->stats_info_copy(iter, avail);
		avail -= min(avail, part);
		total += part;
	}

	up_read(&rds_trans_sem);

	return total;
}

