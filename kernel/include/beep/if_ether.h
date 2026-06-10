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
#ifndef _BEEP_IF_ETHER_H
#define _BEEP_IF_ETHER_H

#include <beep/skbuff.h>
#include <uapi/beep/if_ether.h>

static inline struct ethhdr *eth_hdr(const struct sk_buff *skb)
{
	return (struct ethhdr *)skb_mac_header(skb);
}

int eth_header_parse(const struct sk_buff *skb, unsigned char *haddr);

int mac_pton(const char *s, u8 *mac);
extern ssize_t sysfs_format_mac(char *buf, const unsigned char *addr, int len);

#endif	/* _BEEP_IF_ETHER_H */
