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
#ifndef __MUSB_OMAP_H__
#define __MUSB_OMAP_H__

enum omap_musb_vbus_id_status {
	OMAP_MUSB_UNKNOWN = 0,
	OMAP_MUSB_ID_GROUND,
	OMAP_MUSB_ID_FLOAT,
	OMAP_MUSB_VBUS_VALID,
	OMAP_MUSB_VBUS_OFF,
};

#if (defined(CONFIG_USB_MUSB_OMAP2PLUS) || \
				defined(CONFIG_USB_MUSB_OMAP2PLUS_MODULE))
void omap_musb_mailbox(enum omap_musb_vbus_id_status status);
#else
static inline void omap_musb_mailbox(enum omap_musb_vbus_id_status status)
{
}
#endif

#endif	/* __MUSB_OMAP_H__ */
