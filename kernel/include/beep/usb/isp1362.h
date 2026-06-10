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
#ifndef __BEEP_USB_ISP1362_H__
#define __BEEP_USB_ISP1362_H__

struct isp1362_platform_data {
	/* Enable internal pulldown resistors on downstream ports */
	unsigned sel15Kres:1;
	/* Clock cannot be stopped */
	unsigned clknotstop:1;
	/* On-chip overcurrent protection */
	unsigned oc_enable:1;
	/* INT output polarity */
	unsigned int_act_high:1;
	/* INT edge or level triggered */
	unsigned int_edge_triggered:1;
	/* DREQ output polarity */
	unsigned dreq_act_high:1;
	/* DACK input polarity */
	unsigned dack_act_high:1;
	/* chip can be resumed via H_WAKEUP pin */
	unsigned remote_wakeup_connected:1;
	/* Switch or not to switch (keep always powered) */
	unsigned no_power_switching:1;
	/* Ganged port power switching (0) or individual port power switching (1) */
	unsigned power_switching_mode:1;
	/* Given port_power, msec/2 after power on till power good */
	u8 potpg;
	/* Hardware reset set/clear */
	void (*reset) (struct device *dev, int set);
	/* Clock start/stop */
	void (*clock) (struct device *dev, int start);
	/* Inter-io delay (ns). The chip is picky about access timings; it
	 * expects at least:
	 * 110ns delay between consecutive accesses to DATA_REG,
	 * 300ns delay between access to ADDR_REG and DATA_REG (registers)
	 * 462ns delay between access to ADDR_REG and DATA_REG (buffer memory)
	 * WE MUST NOT be activated during these intervals (even without CS!)
	 */
	void (*delay) (struct device *dev, unsigned int delay);
};

#endif
