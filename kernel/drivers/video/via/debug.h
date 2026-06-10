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
#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifndef VIAFB_DEBUG
#define VIAFB_DEBUG 0
#endif

#if VIAFB_DEBUG
#define DEBUG_MSG(f, a...)   printk(f, ## a)
#else
#define DEBUG_MSG(f, a...)
#endif

#define VIAFB_WARN 0
#if VIAFB_WARN
#define WARN_MSG(f, a...)   printk(f, ## a)
#else
#define WARN_MSG(f, a...)
#endif

#endif /* __DEBUG_H__ */
