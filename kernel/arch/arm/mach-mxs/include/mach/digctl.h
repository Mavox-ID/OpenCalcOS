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
#ifndef __MACH_DIGCTL_H__
#define __MACH_DIGCTL_H__

/* MXS DIGCTL SAIF CLKMUX */
#define MXS_DIGCTL_SAIF_CLKMUX_DIRECT		0x0
#define MXS_DIGCTL_SAIF_CLKMUX_CROSSINPUT	0x1
#define MXS_DIGCTL_SAIF_CLKMUX_EXTMSTR0		0x2
#define MXS_DIGCTL_SAIF_CLKMUX_EXTMSTR1		0x3

#define HW_DIGCTL_CTRL			0x0
#define  BP_DIGCTL_CTRL_SAIF_CLKMUX	10
#define  BM_DIGCTL_CTRL_SAIF_CLKMUX	(0x3 << 10)
#define HW_DIGCTL_CHIPID		0x310
#endif
