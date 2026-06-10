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
#ifndef _UAPI__HDLC_H
#define _UAPI__HDLC_H


#define HDLC_MAX_MTU 1500	/* Ethernet 1500 bytes */
#if 0
#define HDLC_MAX_MRU (HDLC_MAX_MTU + 10 + 14 + 4) /* for ETH+VLAN over FR */
#else
#define HDLC_MAX_MRU 1600 /* as required for FR network */
#endif


#endif /* _UAPI__HDLC_H */
