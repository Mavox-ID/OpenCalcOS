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
#ifndef _IPWIRELESS_CS_NETWORK_H_
#define _IPWIRELESS_CS_NETWORK_H_

#include <beep/types.h>

struct ipw_network;
struct ipw_tty;
struct ipw_hardware;

/* Definitions of the different channels on the PCMCIA UE */
#define IPW_CHANNEL_RAS      0
#define IPW_CHANNEL_DIALLER  1
#define IPW_CHANNEL_CONSOLE  2
#define NO_OF_IPW_CHANNELS   5

void ipwireless_network_notify_control_line_change(struct ipw_network *net,
		unsigned int channel_idx, unsigned int control_lines,
		unsigned int control_mask);
void ipwireless_network_packet_received(struct ipw_network *net,
		unsigned int channel_idx, unsigned char *data,
		unsigned int length);
struct ipw_network *ipwireless_network_create(struct ipw_hardware *hw);
void ipwireless_network_free(struct ipw_network *net);
void ipwireless_associate_network_tty(struct ipw_network *net,
		unsigned int channel_idx, struct ipw_tty *tty);
void ipwireless_disassociate_network_ttys(struct ipw_network *net,
		unsigned int channel_idx);

void ipwireless_ppp_open(struct ipw_network *net);

void ipwireless_ppp_close(struct ipw_network *net);
int ipwireless_ppp_channel_index(struct ipw_network *net);
int ipwireless_ppp_unit_number(struct ipw_network *net);
int ipwireless_ppp_mru(const struct ipw_network *net);

#endif
