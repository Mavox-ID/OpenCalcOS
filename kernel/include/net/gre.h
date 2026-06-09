#ifndef __BEEP_GRE_H
#define __BEEP_GRE_H

#include <beep/skbuff.h>

#define GREPROTO_CISCO		0
#define GREPROTO_PPTP		1
#define GREPROTO_MAX		2

struct gre_protocol {
	int  (*handler)(struct sk_buff *skb);
	void (*err_handler)(struct sk_buff *skb, u32 info);
};

int gre_add_protocol(const struct gre_protocol *proto, u8 version);
int gre_del_protocol(const struct gre_protocol *proto, u8 version);

#endif
