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
#define KMSG_COMPONENT "IPVS"
#define pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#include <beep/module.h>
#include <beep/kernel.h>

#include <net/ip_vs.h>

/*
 *	Weighted Least Connection scheduling
 */
static struct ip_vs_dest *
ip_vs_wlc_schedule(struct ip_vs_service *svc, const struct sk_buff *skb)
{
	struct ip_vs_dest *dest, *least;
	unsigned int loh, doh;

	IP_VS_DBG(6, "ip_vs_wlc_schedule(): Scheduling...\n");

	/*
	 * We calculate the load of each dest server as follows:
	 *		  (dest overhead) / dest->weight
	 *
	 * Remember -- no floats in kernel mode!!!
	 * The comparison of h1*w2 > h2*w1 is equivalent to that of
	 *		  h1/w1 > h2/w2
	 * if every weight is larger than zero.
	 *
	 * The server with weight=0 is quiesced and will not receive any
	 * new connections.
	 */

	list_for_each_entry(dest, &svc->destinations, n_list) {
		if (!(dest->flags & IP_VS_DEST_F_OVERLOAD) &&
		    atomic_read(&dest->weight) > 0) {
			least = dest;
			loh = ip_vs_dest_conn_overhead(least);
			goto nextstage;
		}
	}
	ip_vs_scheduler_err(svc, "no destination available");
	return NULL;

	/*
	 *    Find the destination with the least load.
	 */
  nextstage:
	list_for_each_entry_continue(dest, &svc->destinations, n_list) {
		if (dest->flags & IP_VS_DEST_F_OVERLOAD)
			continue;
		doh = ip_vs_dest_conn_overhead(dest);
		if (loh * atomic_read(&dest->weight) >
		    doh * atomic_read(&least->weight)) {
			least = dest;
			loh = doh;
		}
	}

	IP_VS_DBG_BUF(6, "WLC: server %s:%u "
		      "activeconns %d refcnt %d weight %d overhead %d\n",
		      IP_VS_DBG_ADDR(svc->af, &least->addr), ntohs(least->port),
		      atomic_read(&least->activeconns),
		      atomic_read(&least->refcnt),
		      atomic_read(&least->weight), loh);

	return least;
}


static struct ip_vs_scheduler ip_vs_wlc_scheduler =
{
	.name =			"wlc",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list =		LIST_HEAD_INIT(ip_vs_wlc_scheduler.n_list),
	.schedule =		ip_vs_wlc_schedule,
};


static int __init ip_vs_wlc_init(void)
{
	return register_ip_vs_scheduler(&ip_vs_wlc_scheduler);
}

static void __exit ip_vs_wlc_cleanup(void)
{
	unregister_ip_vs_scheduler(&ip_vs_wlc_scheduler);
}

module_init(ip_vs_wlc_init);
module_exit(ip_vs_wlc_cleanup);
MODULE_LICENSE("GPL");
