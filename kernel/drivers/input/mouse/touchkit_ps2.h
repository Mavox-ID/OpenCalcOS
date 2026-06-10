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
#ifndef _TOUCHKIT_PS2_H
#define _TOUCHKIT_PS2_H

#ifdef CONFIG_MOUSE_PS2_TOUCHKIT
int touchkit_ps2_detect(struct psmouse *psmouse, bool set_properties);
#else
static inline int touchkit_ps2_detect(struct psmouse *psmouse,
				      bool set_properties)
{
	return -ENOSYS;
}
#endif /* CONFIG_MOUSE_PS2_TOUCHKIT */

#endif
