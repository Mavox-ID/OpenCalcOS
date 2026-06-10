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
#include <beep/skbuff.h>
#include <beep/random.h>
#include <beep/seq_file.h>

#include <net/irda/irlan_common.h>
#include <net/irda/irlan_filter.h>

/*
 * Function irlan_filter_request (self, skb)
 *
 *    Handle filter request from client peer device
 *
 */
void irlan_filter_request(struct irlan_cb *self, struct sk_buff *skb)
{
	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == IRLAN_MAGIC, return;);

	if ((self->provider.filter_type == IRLAN_DIRECTED) &&
	    (self->provider.filter_operation == DYNAMIC))
	{
		IRDA_DEBUG(0, "Giving peer a dynamic Ethernet address\n");
		self->provider.mac_address[0] = 0x40;
		self->provider.mac_address[1] = 0x00;
		self->provider.mac_address[2] = 0x00;
		self->provider.mac_address[3] = 0x00;

		/* Use arbitration value to generate MAC address */
		if (self->provider.access_type == ACCESS_PEER) {
			self->provider.mac_address[4] =
				self->provider.send_arb_val & 0xff;
			self->provider.mac_address[5] =
				(self->provider.send_arb_val >> 8) & 0xff;
		} else {
			/* Just generate something for now */
			get_random_bytes(self->provider.mac_address+4, 1);
			get_random_bytes(self->provider.mac_address+5, 1);
		}

		skb->data[0] = 0x00; /* Success */
		skb->data[1] = 0x03;
		irlan_insert_string_param(skb, "FILTER_MODE", "NONE");
		irlan_insert_short_param(skb, "MAX_ENTRY", 0x0001);
		irlan_insert_array_param(skb, "FILTER_ENTRY",
					 self->provider.mac_address, 6);
		return;
	}

	if ((self->provider.filter_type == IRLAN_DIRECTED) &&
	    (self->provider.filter_mode == FILTER))
	{
		IRDA_DEBUG(0, "Directed filter on\n");
		skb->data[0] = 0x00; /* Success */
		skb->data[1] = 0x00;
		return;
	}
	if ((self->provider.filter_type == IRLAN_DIRECTED) &&
	    (self->provider.filter_mode == NONE))
	{
		IRDA_DEBUG(0, "Directed filter off\n");
		skb->data[0] = 0x00; /* Success */
		skb->data[1] = 0x00;
		return;
	}

	if ((self->provider.filter_type == IRLAN_BROADCAST) &&
	    (self->provider.filter_mode == FILTER))
	{
		IRDA_DEBUG(0, "Broadcast filter on\n");
		skb->data[0] = 0x00; /* Success */
		skb->data[1] = 0x00;
		return;
	}
	if ((self->provider.filter_type == IRLAN_BROADCAST) &&
	    (self->provider.filter_mode == NONE))
	{
		IRDA_DEBUG(0, "Broadcast filter off\n");
		skb->data[0] = 0x00; /* Success */
		skb->data[1] = 0x00;
		return;
	}
	if ((self->provider.filter_type == IRLAN_MULTICAST) &&
	    (self->provider.filter_mode == FILTER))
	{
		IRDA_DEBUG(0, "Multicast filter on\n");
		skb->data[0] = 0x00; /* Success */
		skb->data[1] = 0x00;
		return;
	}
	if ((self->provider.filter_type == IRLAN_MULTICAST) &&
	    (self->provider.filter_mode == NONE))
	{
		IRDA_DEBUG(0, "Multicast filter off\n");
		skb->data[0] = 0x00; /* Success */
		skb->data[1] = 0x00;
		return;
	}
	if ((self->provider.filter_type == IRLAN_MULTICAST) &&
	    (self->provider.filter_operation == GET))
	{
		IRDA_DEBUG(0, "Multicast filter get\n");
		skb->data[0] = 0x00; /* Success? */
		skb->data[1] = 0x02;
		irlan_insert_string_param(skb, "FILTER_MODE", "NONE");
		irlan_insert_short_param(skb, "MAX_ENTRY", 16);
		return;
	}
	skb->data[0] = 0x00; /* Command not supported */
	skb->data[1] = 0x00;

	IRDA_DEBUG(0, "Not implemented!\n");
}

/*
 * Function check_request_param (self, param, value)
 *
 *    Check parameters in request from peer device
 *
 */
void irlan_check_command_param(struct irlan_cb *self, char *param, char *value)
{
	IRDA_DEBUG(4, "%s()\n", __func__ );

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == IRLAN_MAGIC, return;);

	IRDA_DEBUG(4, "%s, %s\n", param, value);

	/*
	 *  This is experimental!! DB.
	 */
	 if (strcmp(param, "MODE") == 0) {
		IRDA_DEBUG(0, "%s()\n", __func__ );
		self->use_udata = TRUE;
		return;
	}

	/*
	 *  FILTER_TYPE
	 */
	if (strcmp(param, "FILTER_TYPE") == 0) {
		if (strcmp(value, "DIRECTED") == 0) {
			self->provider.filter_type = IRLAN_DIRECTED;
			return;
		}
		if (strcmp(value, "MULTICAST") == 0) {
			self->provider.filter_type = IRLAN_MULTICAST;
			return;
		}
		if (strcmp(value, "BROADCAST") == 0) {
			self->provider.filter_type = IRLAN_BROADCAST;
			return;
		}
	}
	/*
	 *  FILTER_MODE
	 */
	if (strcmp(param, "FILTER_MODE") == 0) {
		if (strcmp(value, "ALL") == 0) {
			self->provider.filter_mode = ALL;
			return;
		}
		if (strcmp(value, "FILTER") == 0) {
			self->provider.filter_mode = FILTER;
			return;
		}
		if (strcmp(value, "NONE") == 0) {
			self->provider.filter_mode = FILTER;
			return;
		}
	}
	/*
	 *  FILTER_OPERATION
	 */
	if (strcmp(param, "FILTER_OPERATION") == 0) {
		if (strcmp(value, "DYNAMIC") == 0) {
			self->provider.filter_operation = DYNAMIC;
			return;
		}
		if (strcmp(value, "GET") == 0) {
			self->provider.filter_operation = GET;
			return;
		}
	}
}

/*
 * Function irlan_print_filter (filter_type, buf)
 *
 *    Print status of filter. Used by /proc file system
 *
 */
#ifdef CONFIG_PROC_FS
#define MASK2STR(m,s)	{ .mask = m, .str = s }

void irlan_print_filter(struct seq_file *seq, int filter_type)
{
	static struct {
		int mask;
		const char *str;
	} filter_mask2str[] = {
		MASK2STR(IRLAN_DIRECTED,	"DIRECTED"),
		MASK2STR(IRLAN_FUNCTIONAL,	"FUNCTIONAL"),
		MASK2STR(IRLAN_GROUP,		"GROUP"),
		MASK2STR(IRLAN_MAC_FRAME,	"MAC_FRAME"),
		MASK2STR(IRLAN_MULTICAST,	"MULTICAST"),
		MASK2STR(IRLAN_BROADCAST,	"BROADCAST"),
		MASK2STR(IRLAN_IPX_SOCKET,	"IPX_SOCKET"),
		MASK2STR(0,			NULL)
	}, *p;

	for (p = filter_mask2str; p->str; p++) {
		if (filter_type & p->mask)
			seq_printf(seq, "%s ", p->str);
	}
	seq_putc(seq, '\n');
}
#undef MASK2STR
#endif
