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
#ifndef IRLAN_SERVER_H
#define IRLAN_SERVER_H

#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/skbuff.h>
#include <beep/netdevice.h>

#include <net/irda/irlan_common.h>

void irlan_provider_ctrl_disconnect_indication(void *instance, void *sap, 
					       LM_REASON reason, 
					       struct sk_buff *skb);


void irlan_provider_connect_response(struct irlan_cb *, struct tsap_cb *);

int irlan_parse_open_data_cmd(struct irlan_cb *self, struct sk_buff *skb);
int irlan_provider_parse_command(struct irlan_cb *self, int cmd,
				 struct sk_buff *skb);

void irlan_provider_send_reply(struct irlan_cb *self, int command, 
			       int ret_code);
int irlan_provider_open_ctrl_tsap(struct irlan_cb *self);

#endif


