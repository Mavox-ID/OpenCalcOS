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
#ifndef _MWIFIEX_11N_RXREORDER_H_
#define _MWIFIEX_11N_RXREORDER_H_

#define MIN_FLUSH_TIMER_MS		50

#define PKT_TYPE_BAR 0xE7
#define MAX_TID_VALUE			(2 << 11)
#define TWOPOW11			(2 << 10)

#define BLOCKACKPARAM_TID_POS		2
#define BLOCKACKPARAM_AMSDU_SUPP_MASK	0x1
#define BLOCKACKPARAM_WINSIZE_POS	6
#define DELBA_TID_POS			12
#define DELBA_INITIATOR_POS		11
#define TYPE_DELBA_SENT			1
#define TYPE_DELBA_RECEIVE		2
#define IMMEDIATE_BLOCK_ACK		0x2

#define ADDBA_RSP_STATUS_ACCEPT 0

#define MWIFIEX_DEF_11N_RX_SEQ_NUM	0xffff
#define BA_SETUP_MAX_PACKET_THRESHOLD	16
#define BA_SETUP_PACKET_OFFSET		16

enum mwifiex_rxreor_flags {
	RXREOR_FORCE_NO_DROP	= 1<<0,
};

static inline void mwifiex_reset_11n_rx_seq_num(struct mwifiex_private *priv)
{
	memset(priv->rx_seq, 0xff, sizeof(priv->rx_seq));
}

int mwifiex_11n_rx_reorder_pkt(struct mwifiex_private *,
			       u16 seqNum,
			       u16 tid, u8 *ta,
			       u8 pkttype, void *payload);
void mwifiex_del_ba_tbl(struct mwifiex_private *priv, int Tid,
			u8 *PeerMACAddr, u8 type, int initiator);
void mwifiex_11n_ba_stream_timeout(struct mwifiex_private *priv,
				   struct host_cmd_ds_11n_batimeout *event);
int mwifiex_ret_11n_addba_resp(struct mwifiex_private *priv,
			       struct host_cmd_ds_command
			       *resp);
int mwifiex_cmd_11n_delba(struct host_cmd_ds_command *cmd,
			  void *data_buf);
int mwifiex_cmd_11n_addba_rsp_gen(struct mwifiex_private *priv,
				  struct host_cmd_ds_command *cmd,
				  struct host_cmd_ds_11n_addba_req
				  *cmd_addba_req);
int mwifiex_cmd_11n_addba_req(struct host_cmd_ds_command *cmd,
			      void *data_buf);
void mwifiex_11n_cleanup_reorder_tbl(struct mwifiex_private *priv);
struct mwifiex_rx_reorder_tbl *mwifiex_11n_get_rxreorder_tbl(struct
							   mwifiex_private
							   *priv, int tid,
							   u8 *ta);
struct mwifiex_rx_reorder_tbl *
mwifiex_11n_get_rx_reorder_tbl(struct mwifiex_private *priv, int tid, u8 *ta);
void mwifiex_11n_del_rx_reorder_tbl_by_ta(struct mwifiex_private *priv, u8 *ta);
void mwifiex_update_rxreor_flags(struct mwifiex_adapter *adapter, u8 flags);

#endif /* _MWIFIEX_11N_RXREORDER_H_ */
