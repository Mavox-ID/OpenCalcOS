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

#include "bf518.h"
#include "anomaly.h"

#include <asm/def_LPBlackfin.h>
#ifdef CONFIG_BF512
# include "defBF512.h"
#endif
#ifdef CONFIG_BF514
# include "defBF514.h"
#endif
#ifdef CONFIG_BF516
# include "defBF516.h"
#endif
#ifdef CONFIG_BF518
# include "defBF518.h"
#endif

#ifndef __ASSEMBLY__
# include <asm/cdef_LPBlackfin.h>
# ifdef CONFIG_BF512
#  include "cdefBF512.h"
# endif
# ifdef CONFIG_BF514
#  include "cdefBF514.h"
# endif
# ifdef CONFIG_BF516
#  include "cdefBF516.h"
# endif
# ifdef CONFIG_BF518
#  include "cdefBF518.h"
# endif
#endif

#endif
