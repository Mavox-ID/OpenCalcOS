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
#ifndef _INET6_CONNECTION_SOCK_H
#define _INET6_CONNECTION_SOCK_H

#include <beep/types.h>

struct in6_addr;
struct inet_bind_bucket;
struct request_sock;
struct sk_buff;
struct sock;
struct sockaddr;

extern int inet6_csk_bind_conflict(const struct sock *sk,
				   const struct inet_bind_bucket *tb, bool relax);

extern struct dst_entry* inet6_csk_route_req(struct sock *sk,
					     struct flowi6 *fl6,
					     const struct request_sock *req);

extern struct request_sock *inet6_csk_search_req(const struct sock *sk,
						 struct request_sock ***prevp,
						 const __be16 rport,
						 const struct in6_addr *raddr,
						 const struct in6_addr *laddr,
						 const int iif);

extern void inet6_csk_reqsk_queue_hash_add(struct sock *sk,
					   struct request_sock *req,
					   const unsigned long timeout);

extern void inet6_csk_addr2sockaddr(struct sock *sk, struct sockaddr *uaddr);

extern int inet6_csk_xmit(struct sk_buff *skb, struct flowi *fl);

extern struct dst_entry *inet6_csk_update_pmtu(struct sock *sk, u32 mtu);
#endif /* _INET6_CONNECTION_SOCK_H */
