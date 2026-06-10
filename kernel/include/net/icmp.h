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
#ifndef _ICMP_H
#define	_ICMP_H

#include <beep/icmp.h>

#include <net/inet_sock.h>
#include <net/snmp.h>

struct icmp_err {
  int		errno;
  unsigned int	fatal:1;
};

extern const struct icmp_err icmp_err_convert[];
#define ICMP_INC_STATS(net, field)	SNMP_INC_STATS((net)->mib.icmp_statistics, field)
#define ICMP_INC_STATS_BH(net, field)	SNMP_INC_STATS_BH((net)->mib.icmp_statistics, field)
#define ICMPMSGOUT_INC_STATS(net, field)	SNMP_INC_STATS_ATOMIC_LONG((net)->mib.icmpmsg_statistics, field+256)
#define ICMPMSGIN_INC_STATS_BH(net, field)	SNMP_INC_STATS_ATOMIC_LONG((net)->mib.icmpmsg_statistics, field)

struct dst_entry;
struct net_proto_family;
struct sk_buff;
struct net;

extern void	icmp_send(struct sk_buff *skb_in,  int type, int code, __be32 info);
extern int	icmp_rcv(struct sk_buff *skb);
extern int	icmp_init(void);
extern void	icmp_out_count(struct net *net, unsigned char type);

#endif	/* _ICMP_H */
