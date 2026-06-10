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
#ifndef _IPWIRELESS_CS_HARDWARE_H_
#define _IPWIRELESS_CS_HARDWARE_H_

#include <beep/types.h>
#include <beep/sched.h>
#include <beep/interrupt.h>

#define IPW_CONTROL_LINE_CTS 0x0001
#define IPW_CONTROL_LINE_DCD 0x0002
#define IPW_CONTROL_LINE_DSR 0x0004
#define IPW_CONTROL_LINE_RI  0x0008
#define IPW_CONTROL_LINE_DTR 0x0010
#define IPW_CONTROL_LINE_RTS 0x0020

struct ipw_hardware;
struct ipw_network;

struct ipw_hardware *ipwireless_hardware_create(void);
void ipwireless_hardware_free(struct ipw_hardware *hw);
irqreturn_t ipwireless_interrupt(int irq, void *dev_id);
int ipwireless_set_DTR(struct ipw_hardware *hw, unsigned int channel_idx,
		int state);
int ipwireless_set_RTS(struct ipw_hardware *hw, unsigned int channel_idx,
		int state);
int ipwireless_send_packet(struct ipw_hardware *hw,
			    unsigned int channel_idx,
			    const unsigned char *data,
			    unsigned int length,
			    void (*packet_sent_callback) (void *cb,
							  unsigned int length),
			    void *sent_cb_data);
void ipwireless_associate_network(struct ipw_hardware *hw,
		struct ipw_network *net);
void ipwireless_stop_interrupts(struct ipw_hardware *hw);
void ipwireless_init_hardware_v1(struct ipw_hardware *hw,
				 unsigned int base_port,
				 void __iomem *attr_memory,
				 void __iomem *common_memory,
				 int is_v2_card,
				 void (*reboot_cb) (void *data),
				 void *reboot_cb_data);
void ipwireless_init_hardware_v2_v3(struct ipw_hardware *hw);
void ipwireless_sleep(unsigned int tenths);

#endif
