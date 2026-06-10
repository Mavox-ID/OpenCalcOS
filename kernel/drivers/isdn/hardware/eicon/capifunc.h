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
#ifndef __CAPIFUNC_H__
#define __CAPIFUNC_H__

#define DRRELMAJOR  2
#define DRRELMINOR  0
#define DRRELEXTRA  ""

#define M_COMPANY "Eicon Networks"

extern char DRIVERRELEASE_CAPI[];

typedef struct _diva_card {
	struct list_head list;
	int remove_in_progress;
	int Id;
	struct capi_ctr capi_ctrl;
	DIVA_CAPI_ADAPTER *adapter;
	DESCRIPTOR d;
	char name[32];
} diva_card;

/*
 * prototypes
 */
int init_capifunc(void);
void finit_capifunc(void);

#endif /* __CAPIFUNC_H__ */
