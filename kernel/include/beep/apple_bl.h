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
#ifndef _BEEP_APPLE_BL_H
#define _BEEP_APPLE_BL_H

#if defined(CONFIG_BACKLIGHT_APPLE) || defined(CONFIG_BACKLIGHT_APPLE_MODULE)

extern int apple_bl_register(void);
extern void apple_bl_unregister(void);

#else /* !CONFIG_BACKLIGHT_APPLE */

static inline int apple_bl_register(void)
{
	return 0;
}

static inline void apple_bl_unregister(void)
{
}

#endif /* !CONFIG_BACKLIGHT_APPLE */

#endif /* _BEEP_APPLE_BL_H */
