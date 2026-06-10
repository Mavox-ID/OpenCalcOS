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
#ifndef __BEEP_LLC_H
#define __BEEP_LLC_H

#include <uapi/beep/llc.h>

#define LLC_SAP_DYN_START	0xC0
#define LLC_SAP_DYN_STOP	0xDE
#define LLC_SAP_DYN_TRIES	4

#define llc_ui_skb_cb(__skb) ((struct sockaddr_llc *)&((__skb)->cb[0]))
#endif /* __BEEP_LLC_H */
