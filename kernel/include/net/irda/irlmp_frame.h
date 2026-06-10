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
#ifndef IRMLP_FRAME_H
#define IRMLP_FRAME_H

#include <beep/skbuff.h>

#include <net/irda/discovery.h>

/* IrLMP frame opcodes */
#define CONNECT_CMD    0x01
#define CONNECT_CNF    0x81
#define DISCONNECT     0x02
#define ACCESSMODE_CMD 0x03
#define ACCESSMODE_CNF 0x83

#define CONTROL_BIT    0x80

void irlmp_send_data_pdu(struct lap_cb *self, __u8 dlsap, __u8 slsap,
				int expedited, struct sk_buff *skb);
void irlmp_send_lcf_pdu(struct lap_cb *self, __u8 dlsap, __u8 slsap, 
			__u8 opcode, struct sk_buff *skb);
void irlmp_link_data_indication(struct lap_cb *, struct sk_buff *, 
				int unreliable);
#ifdef CONFIG_IRDA_ULTRA
void irlmp_link_unitdata_indication(struct lap_cb *, struct sk_buff *);
#endif /* CONFIG_IRDA_ULTRA */

void irlmp_link_connect_indication(struct lap_cb *, __u32 saddr, __u32 daddr,
				   struct qos_info *qos, struct sk_buff *skb);
void irlmp_link_connect_request(__u32 daddr);
void irlmp_link_connect_confirm(struct lap_cb *self, struct qos_info *qos, 
				struct sk_buff *skb);
void irlmp_link_disconnect_indication(struct lap_cb *, struct irlap_cb *, 
				      LAP_REASON reason, struct sk_buff *); 
void irlmp_link_discovery_confirm(struct lap_cb *self, hashbin_t *log);
void irlmp_link_discovery_indication(struct lap_cb *, discovery_t *discovery);

#endif
