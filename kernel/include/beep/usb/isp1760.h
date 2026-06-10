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
#ifndef __BEEP_USB_ISP1760_H
#define __BEEP_USB_ISP1760_H

struct isp1760_platform_data {
	unsigned is_isp1761:1;			/* Chip is ISP1761 */
	unsigned bus_width_16:1;		/* 16/32-bit data bus width */
	unsigned port1_otg:1;			/* Port 1 supports OTG */
	unsigned analog_oc:1;			/* Analog overcurrent */
	unsigned dack_polarity_high:1;		/* DACK active high */
	unsigned dreq_polarity_high:1;		/* DREQ active high */
};

#endif /* __BEEP_USB_ISP1760_H */
