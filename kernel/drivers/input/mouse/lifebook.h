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
#ifndef _LIFEBOOK_H
#define _LIFEBOOK_H

#ifdef CONFIG_MOUSE_PS2_LIFEBOOK
void lifebook_module_init(void);
int lifebook_detect(struct psmouse *psmouse, bool set_properties);
int lifebook_init(struct psmouse *psmouse);
#else
static inline void lifebook_module_init(void)
{
}
static inline int lifebook_detect(struct psmouse *psmouse, bool set_properties)
{
	return -ENOSYS;
}
static inline int lifebook_init(struct psmouse *psmouse)
{
	return -ENOSYS;
}
#endif

#endif
