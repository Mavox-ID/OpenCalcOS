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
#ifndef __BESTCOMM_GEN_BD_H__
#define __BESTCOMM_GEN_BD_H__

struct bcom_gen_bd {
	u32	status;
	u32	buf_pa;
};


extern struct bcom_task *
bcom_gen_bd_rx_init(int queue_len, phys_addr_t fifo,
			int initiator, int ipr, int maxbufsize);

extern int
bcom_gen_bd_rx_reset(struct bcom_task *tsk);

extern void
bcom_gen_bd_rx_release(struct bcom_task *tsk);


extern struct bcom_task *
bcom_gen_bd_tx_init(int queue_len, phys_addr_t fifo,
			int initiator, int ipr);

extern int
bcom_gen_bd_tx_reset(struct bcom_task *tsk);

extern void
bcom_gen_bd_tx_release(struct bcom_task *tsk);


/* PSC support utility wrappers */
struct bcom_task * bcom_psc_gen_bd_rx_init(unsigned psc_num, int queue_len,
					   phys_addr_t fifo, int maxbufsize);
struct bcom_task * bcom_psc_gen_bd_tx_init(unsigned psc_num, int queue_len,
					   phys_addr_t fifo);
#endif  /* __BESTCOMM_GEN_BD_H__ */

