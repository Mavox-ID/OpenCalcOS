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
#ifndef _IPWIRELESS_CS_TTY_H_
#define _IPWIRELESS_CS_TTY_H_

#include <beep/types.h>
#include <beep/sched.h>

#include <pcmcia/cistpl.h>
#include <pcmcia/ds.h>

struct ipw_tty;
struct ipw_network;
struct ipw_hardware;

int ipwireless_tty_init(void);
void ipwireless_tty_release(void);

struct ipw_tty *ipwireless_tty_create(struct ipw_hardware *hw,
				      struct ipw_network *net);
void ipwireless_tty_free(struct ipw_tty *tty);
void ipwireless_tty_received(struct ipw_tty *tty, unsigned char *data,
			     unsigned int length);
int ipwireless_tty_is_modem(struct ipw_tty *tty);
void ipwireless_tty_notify_control_line_change(struct ipw_tty *tty,
					       unsigned int channel_idx,
					       unsigned int control_lines,
					       unsigned int changed_mask);

#endif
