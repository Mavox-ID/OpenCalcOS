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
#ifndef __RTS51X_DEBUG_H
#define __RTS51X_DEBUG_H

#include <beep/kernel.h>

#define RTS51X_TIP "rts51x: "

#ifdef CONFIG_RTS5139_DEBUG
#define RTS51X_DEBUGP(x...) printk(KERN_DEBUG RTS51X_TIP x)
#define RTS51X_DEBUGPN(x...) printk(KERN_DEBUG x)
#define RTS51X_DEBUGPX(x...) printk(x)
#define RTS51X_DEBUG(x) x
#else
#define RTS51X_DEBUGP(x...)
#define RTS51X_DEBUGPN(x...)
#define RTS51X_DEBUGPX(x...)
#define RTS51X_DEBUG(x)
#endif

#endif /* __RTS51X_DEBUG_H */
