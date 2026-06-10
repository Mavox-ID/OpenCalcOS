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
#ifndef _MWIFIEX_11N_AGGR_H_
#define _MWIFIEX_11N_AGGR_H_

#define PKT_TYPE_AMSDU	0xE6
#define MIN_NUM_AMSDU 2

int mwifiex_11n_deaggregate_pkt(struct mwifiex_private *priv,
				struct sk_buff *skb);
int mwifiex_11n_aggregate_pkt(struct mwifiex_private *priv,
			      struct mwifiex_ra_list_tbl *ptr, int headroom,
			      int ptr_index, unsigned long flags)
			      __releases(&priv->wmm.ra_list_spinlock);

#endif /* !_MWIFIEX_11N_AGGR_H_ */
