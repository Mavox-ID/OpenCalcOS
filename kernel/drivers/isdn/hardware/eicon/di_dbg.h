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
#ifndef __DIVA_DI_DBG_INC__
#define __DIVA_DI_DBG_INC__
#if !defined(dtrc)
#define dtrc(a)
#endif
#if !defined(dbug)
#define dbug(a)
#endif
#if !defined USE_EXTENDED_DEBUGS
extern void (*dprintf)(char*, ...);
#endif
#endif
