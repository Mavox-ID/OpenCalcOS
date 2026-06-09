#ifndef _IF_TUNNEL_H_
#define _IF_TUNNEL_H_

#include <beep/ip.h>
#include <beep/in6.h>
#include <uapi/beep/if_tunnel.h>
#include <beep/u64_stats_sync.h>

/*
 * Locking : hash tables are protected by RCU and RTNL
 */

#define for_each_ip_tunnel_rcu(pos, start) \
	for (pos = rcu_dereference(start); pos; pos = rcu_dereference(pos->next))

/* often modified stats are per cpu, other are shared (netdev->stats) */
struct pcpu_tstats {
	u64	rx_packets;
	u64	rx_bytes;
	u64	tx_packets;
	u64	tx_bytes;
	struct u64_stats_sync	syncp;
};

#endif /* _IF_TUNNEL_H_ */
