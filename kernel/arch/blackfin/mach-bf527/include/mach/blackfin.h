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

#include "bf527.h"
#include "anomaly.h"

#include <asm/def_LPBlackfin.h>
#if defined(CONFIG_BF523) || defined(CONFIG_BF522)
# include "defBF522.h"
#endif
#if defined(CONFIG_BF525) || defined(CONFIG_BF524)
# include "defBF525.h"
#endif
#if defined(CONFIG_BF527) || defined(CONFIG_BF526)
# include "defBF527.h"
#endif

#if !defined(__ASSEMBLY__)
# include <asm/cdef_LPBlackfin.h>
# if defined(CONFIG_BF523) || defined(CONFIG_BF522)
#  include "cdefBF522.h"
# endif
# if defined(CONFIG_BF525) || defined(CONFIG_BF524)
#  include "cdefBF525.h"
# endif
# if defined(CONFIG_BF527) || defined(CONFIG_BF526)
#  include "cdefBF527.h"
# endif
#endif

#endif
