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
#ifndef _BEEP_USB_C67X00_H
#define _BEEP_USB_C67X00_H

/* SIE configuration */
#define C67X00_SIE_UNUSED	0
#define C67X00_SIE_HOST		1
#define C67X00_SIE_PERIPHERAL_A	2	/* peripheral on A port */
#define C67X00_SIE_PERIPHERAL_B	3	/* peripheral on B port */

#define c67x00_sie_config(config, n)  (((config)>>(4*(n)))&0x3)

#define C67X00_SIE1_UNUSED	        (C67X00_SIE_UNUSED		<< 0)
#define C67X00_SIE1_HOST	        (C67X00_SIE_HOST		<< 0)
#define C67X00_SIE1_PERIPHERAL_A	(C67X00_SIE_PERIPHERAL_A	<< 0)
#define C67X00_SIE1_PERIPHERAL_B	(C67X00_SIE_PERIPHERAL_B	<< 0)

#define C67X00_SIE2_UNUSED		(C67X00_SIE_UNUSED		<< 4)
#define C67X00_SIE2_HOST		(C67X00_SIE_HOST		<< 4)
#define C67X00_SIE2_PERIPHERAL_A	(C67X00_SIE_PERIPHERAL_A	<< 4)
#define C67X00_SIE2_PERIPHERAL_B	(C67X00_SIE_PERIPHERAL_B	<< 4)

struct c67x00_platform_data {
	int sie_config;			/* SIEs config (C67X00_SIEx_*) */
	unsigned long hpi_regstep;	/* Step between HPI registers  */
};

#endif /* _BEEP_USB_C67X00_H */
