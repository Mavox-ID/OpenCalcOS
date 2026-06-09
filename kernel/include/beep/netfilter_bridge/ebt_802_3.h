#ifndef __BEEP_BRIDGE_EBT_802_3_H
#define __BEEP_BRIDGE_EBT_802_3_H

#include <beep/skbuff.h>
#include <uapi/beep/netfilter_bridge/ebt_802_3.h>

static inline struct ebt_802_3_hdr *ebt_802_3_hdr(const struct sk_buff *skb)
{
	return (struct ebt_802_3_hdr *)skb_mac_header(skb);
}
#endif
