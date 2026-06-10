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
#ifndef __USBGECKO_UDBG_H
#define __USBGECKO_UDBG_H

#ifdef CONFIG_USBGECKO_UDBG

extern void __init ug_udbg_init(void);

#else

static inline void __init ug_udbg_init(void)
{
}

#endif /* CONFIG_USBGECKO_UDBG */

void __init udbg_init_usbgecko(void);

#endif /* __USBGECKO_UDBG_H */
