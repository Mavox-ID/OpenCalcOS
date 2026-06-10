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
#ifndef __CXGB3I_H__
#define __CXGB3I_H__

#define CXGB3I_SCSI_HOST_QDEPTH 1024
#define CXGB3I_MAX_LUN		512
#define ISCSI_PDU_NONPAYLOAD_MAX \
	(sizeof(struct iscsi_hdr) + ISCSI_MAX_AHS_SIZE + 2*ISCSI_DIGEST_SIZE)

/*for TX: a skb must have a headroom of at least TX_HEADER_LEN bytes */
#define CXGB3I_TX_HEADER_LEN \
	(sizeof(struct tx_data_wr) + sizeof(struct sge_opaque_hdr))

extern cxgb3_cpl_handler_func cxgb3i_cpl_handlers[NUM_CPL_CMDS];

static inline unsigned int cxgb3i_get_private_ipv4addr(struct net_device *ndev)
{
	return ((struct port_info *)(netdev_priv(ndev)))->iscsi_ipv4addr;
}

static inline void cxgb3i_set_private_ipv4addr(struct net_device *ndev,
						unsigned int addr)
{
	struct port_info *pi =  (struct port_info *)netdev_priv(ndev);

	pi->iscsic.flags = addr ? 1 : 0;
	pi->iscsi_ipv4addr = addr;
	if (addr)
		memcpy(pi->iscsic.mac_addr, ndev->dev_addr, ETH_ALEN);
}

struct cpl_iscsi_hdr_norss {
	union opcode_tid ot;
	u16 pdu_len_ddp;
	u16 len;
	u32 seq;
	u16 urg;
	u8 rsvd;
	u8 status;
};

struct cpl_rx_data_ddp_norss {
	union opcode_tid ot;
	u16 urg;
	u16 len;
	u32 seq;
	u32 nxt_seq;
	u32 ulp_crc;
	u32 ddp_status;
};
#endif
