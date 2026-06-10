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
#ifndef LPC_ICH_H
#define LPC_ICH_H

/* Watchdog resources */
#define ICH_RES_IO_TCO	0
#define ICH_RES_IO_SMI	1
#define ICH_RES_MEM_OFF	2
#define ICH_RES_MEM_GCS	0

/* GPIO resources */
#define ICH_RES_GPIO	0
#define ICH_RES_GPE0	1

/* GPIO compatibility */
#define ICH_I3100_GPIO		0x401
#define ICH_V5_GPIO		0x501
#define ICH_V6_GPIO		0x601
#define ICH_V7_GPIO		0x701
#define ICH_V9_GPIO		0x801
#define ICH_V10CORP_GPIO	0xa01
#define ICH_V10CONS_GPIO	0xa11

struct lpc_ich_info {
	char name[32];
	unsigned int iTCO_version;
	unsigned int gpio_version;
	u8 use_gpio;
};

#endif
