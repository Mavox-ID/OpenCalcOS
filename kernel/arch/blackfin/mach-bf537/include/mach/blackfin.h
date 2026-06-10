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
#ifndef _MACH_BLACKFIN_H_
#define _MACH_BLACKFIN_H_

#define BF537_FAMILY

#include "bf537.h"
#include "anomaly.h"

#include <asm/def_LPBlackfin.h>
#ifdef CONFIG_BF534
# include "defBF534.h"
#endif
#if defined(CONFIG_BF537) || defined(CONFIG_BF536)
# include "defBF537.h"
#endif

#if !defined(__ASSEMBLY__)
# include <asm/cdef_LPBlackfin.h>
# ifdef CONFIG_BF534
#  include "cdefBF534.h"
# endif
# if defined(CONFIG_BF537) || defined(CONFIG_BF536)
#  include "cdefBF537.h"
# endif
#endif

#endif
