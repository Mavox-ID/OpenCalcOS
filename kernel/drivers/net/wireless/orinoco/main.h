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
#ifndef _ORINOCO_MAIN_H_
#define _ORINOCO_MAIN_H_

#include <beep/ieee80211.h>
#include "orinoco.h"

/********************************************************************/
/* Compile time configuration and compatibility stuff               */
/********************************************************************/

/* We do this this way to avoid ifdefs in the actual code */
#ifdef WIRELESS_SPY
#define SPY_NUMBER(priv)	(priv->spy_data.spy_number)
#else
#define SPY_NUMBER(priv)	0
#endif /* WIRELESS_SPY */

/********************************************************************/

/* Export module parameter */
extern int force_monitor;

/* Forward declarations */
struct net_device;
struct work_struct;

void set_port_type(struct orinoco_private *priv);
int orinoco_commit(struct orinoco_private *priv);
void orinoco_reset(struct work_struct *work);

/* Information element helpers - find a home for these... */
#define WPA_OUI_TYPE	"\x00\x50\xF2\x01"
#define WPA_SELECTOR_LEN 4
static inline u8 *orinoco_get_wpa_ie(u8 *data, size_t len)
{
	u8 *p = data;
	while ((p + 2 + WPA_SELECTOR_LEN) < (data + len)) {
		if ((p[0] == WLAN_EID_VENDOR_SPECIFIC) &&
		    (memcmp(&p[2], WPA_OUI_TYPE, WPA_SELECTOR_LEN) == 0))
			return p;
		p += p[1] + 2;
	}
	return NULL;
}

#endif /* _ORINOCO_MAIN_H_ */
