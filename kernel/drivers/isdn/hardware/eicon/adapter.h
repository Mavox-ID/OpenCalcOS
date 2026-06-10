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
#ifndef __DIVA_USER_MODE_IDI_ADAPTER_H__
#define __DIVA_USER_MODE_IDI_ADAPTER_H__

#define DIVA_UM_IDI_ADAPTER_REMOVED 0x00000001

typedef struct _diva_um_idi_adapter {
	struct list_head link;
	DESCRIPTOR d;
	int adapter_nr;
	struct list_head entity_q;	/* entities linked to this adapter */
	dword status;
} diva_um_idi_adapter_t;


#endif
