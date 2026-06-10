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
#ifndef _UAPI_ASM_TILE_SIGNAL_H
#define _UAPI_ASM_TILE_SIGNAL_H

/* Do not notify a ptracer when this signal is handled. */
#define SA_NOPTRACE 0x02000000u

/* Used in earlier Tilera releases, so keeping for binary compatibility. */
#define SA_RESTORER 0x04000000u

#include <asm-generic/signal.h>


#endif /* _UAPI_ASM_TILE_SIGNAL_H */
