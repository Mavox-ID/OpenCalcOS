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
#ifndef IRLAN_CLIENT_H
#define IRLAN_CLIENT_H

#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/skbuff.h>
#include <beep/netdevice.h>

#include <net/irda/irias_object.h>
#include <net/irda/irlan_event.h>

void irlan_client_discovery_indication(discinfo_t *, DISCOVERY_MODE, void *);
void irlan_client_wakeup(struct irlan_cb *self, __u32 saddr, __u32 daddr);

void irlan_client_parse_response(struct irlan_cb *self, struct sk_buff *skb);
void irlan_client_get_value_confirm(int result, __u16 obj_id, 
				    struct ias_value *value, void *priv);
#endif
