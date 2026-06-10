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
