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
#ifndef _BRCM_AMPDU_H_
#define _BRCM_AMPDU_H_

/*
 * Data structure representing an in-progress session for accumulating
 * frames for AMPDU.
 *
 * wlc: pointer to common driver data
 * skb_list: queue of skb's for AMPDU
 * max_ampdu_len: maximum length for this AMPDU
 * max_ampdu_frames: maximum number of frames for this AMPDU
 * ampdu_len: total number of bytes accumulated for this AMPDU
 * dma_len: DMA length of this AMPDU
 */
struct brcms_ampdu_session {
	struct brcms_c_info *wlc;
	struct sk_buff_head skb_list;
	unsigned max_ampdu_len;
	u16 max_ampdu_frames;
	u16 ampdu_len;
	u16 dma_len;
};

extern void brcms_c_ampdu_reset_session(struct brcms_ampdu_session *session,
					struct brcms_c_info *wlc);
extern int brcms_c_ampdu_add_frame(struct brcms_ampdu_session *session,
				   struct sk_buff *p);
extern void brcms_c_ampdu_finalize(struct brcms_ampdu_session *session);

extern struct ampdu_info *brcms_c_ampdu_attach(struct brcms_c_info *wlc);
extern void brcms_c_ampdu_detach(struct ampdu_info *ampdu);
extern void brcms_c_ampdu_dotxstatus(struct ampdu_info *ampdu, struct scb *scb,
				 struct sk_buff *p, struct tx_status *txs);
extern void brcms_c_ampdu_macaddr_upd(struct brcms_c_info *wlc);
extern void brcms_c_ampdu_shm_upd(struct ampdu_info *ampdu);

#endif				/* _BRCM_AMPDU_H_ */
