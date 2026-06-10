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
#ifndef __ASMARM_TCM_H
#define __ASMARM_TCM_H

#ifndef CONFIG_HAVE_TCM
#error "You should not be including tcm.h unless you have a TCM!"
#endif

#include <beep/compiler.h>

/* Tag variables with this */
#define __tcmdata __section(.tcm.data)
/* Tag constants with this */
#define __tcmconst __section(.tcm.rodata)
/* Tag functions inside TCM called from outside TCM with this */
#define __tcmfunc __attribute__((long_call)) __section(.tcm.text) noinline
/* Tag function inside TCM called from inside TCM  with this */
#define __tcmlocalfunc __section(.tcm.text)

void *tcm_alloc(size_t len);
void tcm_free(void *addr, size_t len);
bool tcm_dtcm_present(void);
bool tcm_itcm_present(void);

#endif
