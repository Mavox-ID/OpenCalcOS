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

#include "bf548.h"
#include "anomaly.h"

#include <asm/def_LPBlackfin.h>
#ifdef CONFIG_BF542
# include "defBF542.h"
#endif
#ifdef CONFIG_BF544
# include "defBF544.h"
#endif
#ifdef CONFIG_BF547
# include "defBF547.h"
#endif
#ifdef CONFIG_BF548
# include "defBF548.h"
#endif
#ifdef CONFIG_BF549
# include "defBF549.h"
#endif

#ifndef __ASSEMBLY__
# include <asm/cdef_LPBlackfin.h>
# ifdef CONFIG_BF542
#  include "cdefBF542.h"
# endif
# ifdef CONFIG_BF544
#  include "cdefBF544.h"
# endif
# ifdef CONFIG_BF547
#  include "cdefBF547.h"
# endif
# ifdef CONFIG_BF548
#  include "cdefBF548.h"
# endif
# ifdef CONFIG_BF549
#  include "cdefBF549.h"
# endif
#endif

#endif
