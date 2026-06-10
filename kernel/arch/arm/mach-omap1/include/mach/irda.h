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
#ifndef ASMARM_ARCH_IRDA_H
#define ASMARM_ARCH_IRDA_H

/* board specific transceiver capabilities */

#define IR_SEL		1	/* Selects IrDA */
#define IR_SIRMODE	2
#define IR_FIRMODE	4
#define IR_MIRMODE	8

struct omap_irda_config {
	int transceiver_cap;
	int (*transceiver_mode)(struct device *dev, int mode);
	int (*select_irda)(struct device *dev, int state);
	int rx_channel;
	int tx_channel;
	unsigned long dest_start;
	unsigned long src_start;
	int tx_trigger;
	int rx_trigger;
	int mode;
};

#endif
