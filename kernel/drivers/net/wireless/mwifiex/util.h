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
#ifndef _MWIFIEX_UTIL_H_
#define _MWIFIEX_UTIL_H_

static inline struct mwifiex_rxinfo *MWIFIEX_SKB_RXCB(struct sk_buff *skb)
{
	return (struct mwifiex_rxinfo *)(skb->cb + sizeof(phys_addr_t));
}

static inline struct mwifiex_txinfo *MWIFIEX_SKB_TXCB(struct sk_buff *skb)
{
	return (struct mwifiex_txinfo *)(skb->cb + sizeof(phys_addr_t));
}

static inline phys_addr_t *MWIFIEX_SKB_PACB(struct sk_buff *skb)
{
	return (phys_addr_t *)skb->cb;
}
#endif /* !_MWIFIEX_UTIL_H_ */
