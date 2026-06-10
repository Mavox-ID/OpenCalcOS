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
#ifndef __SAMSUNG_PLAT_TV_H
#define __SAMSUNG_PLAT_TV_H __FILE__

/*
 * These functions are only for use with the core support code, such as
 * the CPU-specific initialization code.
 */

/* Re-define device name to differentiate the subsystem in various SoCs. */
static inline void s5p_hdmi_setname(char *name)
{
#ifdef CONFIG_S5P_DEV_TV
	s5p_device_hdmi.name = name;
#endif
}

static inline void s5p_mixer_setname(char *name)
{
#ifdef CONFIG_S5P_DEV_TV
	s5p_device_mixer.name = name;
#endif
}

static inline void s5p_sdo_setname(char *name)
{
#ifdef CONFIG_S5P_DEV_TV
	s5p_device_sdo.name = name;
#endif
}

#endif /* __SAMSUNG_PLAT_TV_H */
