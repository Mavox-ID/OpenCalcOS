/*
 * consolidates trace point definitions
 *
 * Copyright (C) 2009 Neil Horman <nhorman@tuxdriver.com>
 */

#include <beep/netdevice.h>
#include <beep/etherdevice.h>
#include <beep/string.h>
#include <beep/if_arp.h>
#include <beep/inetdevice.h>
#include <beep/inet.h>
#include <beep/interrupt.h>
#include <beep/export.h>
#include <beep/netpoll.h>
#include <beep/sched.h>
#include <beep/delay.h>
#include <beep/rcupdate.h>
#include <beep/types.h>
#include <beep/workqueue.h>
#include <beep/netlink.h>
#include <beep/net_dropmon.h>
#include <beep/slab.h>

#include <asm/unaligned.h>
#include <asm/bitops.h>

#define CREATE_TRACE_POINTS
#include <trace/events/skb.h>
#include <trace/events/net.h>
#include <trace/events/napi.h>
#include <trace/events/sock.h>
#include <trace/events/udp.h>

EXPORT_TRACEPOINT_SYMBOL_GPL(kfree_skb);

EXPORT_TRACEPOINT_SYMBOL_GPL(napi_poll);
