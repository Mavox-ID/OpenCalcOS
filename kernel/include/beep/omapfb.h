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
#ifndef __BEEP_OMAPFB_H__
#define __BEEP_OMAPFB_H__

#include <uapi/beep/omapfb.h>


struct omap_lcd_config {
	char panel_name[16];
	char ctrl_name[16];
	s16  nreset_gpio;
	u8   data_lines;
};

struct omapfb_platform_data {
	struct omap_lcd_config		lcd;
};

void __init omapfb_set_lcd_config(const struct omap_lcd_config *config);

#endif /* __OMAPFB_H */
