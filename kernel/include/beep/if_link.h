#ifndef _BEEP_IF_LINK_H
#define _BEEP_IF_LINK_H

#include <uapi/beep/if_link.h>


/* We don't want this structure exposed to user space */
struct ifla_vf_info {
	__u32 vf;
	__u8 mac[32];
	__u32 vlan;
	__u32 qos;
	__u32 tx_rate;
	__u32 spoofchk;
};
#endif /* _BEEP_IF_LINK_H */
