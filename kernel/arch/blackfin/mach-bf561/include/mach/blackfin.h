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

#define BF561_FAMILY

#include "bf561.h"
#include "anomaly.h"

#include <asm/def_LPBlackfin.h>
#include "defBF561.h"

#ifndef __ASSEMBLY__
# include <asm/cdef_LPBlackfin.h>
# include "cdefBF561.h"
#endif

#define bfin_read_FIO_FLAG_D() bfin_read_FIO0_FLAG_D()
#define bfin_write_FIO_FLAG_D(val) bfin_write_FIO0_FLAG_D(val)
#define bfin_read_FIO_DIR() bfin_read_FIO0_DIR()
#define bfin_write_FIO_DIR(val) bfin_write_FIO0_DIR(val)
#define bfin_read_FIO_INEN() bfin_read_FIO0_INEN()
#define bfin_write_FIO_INEN(val) bfin_write_FIO0_INEN(val)

/* Weird muxer funcs which pick SIC regs from IMASK base */
#define __SIC_MUX(base, x)		((base) + ((x) << 2))
#define bfin_read_SIC_IMASK(x)		bfin_read32(__SIC_MUX(SIC_IMASK0, x))
#define bfin_write_SIC_IMASK(x, val)	bfin_write32(__SIC_MUX(SIC_IMASK0, x), val)
#define bfin_read_SICB_IMASK(x)		bfin_read32(__SIC_MUX(SICB_IMASK0, x))
#define bfin_write_SICB_IMASK(x, val)	bfin_write32(__SIC_MUX(SICB_IMASK0, x), val)
#define bfin_read_SIC_ISR(x)		bfin_read32(__SIC_MUX(SIC_ISR0, x))
#define bfin_write_SIC_ISR(x, val)	bfin_write32(__SIC_MUX(SIC_ISR0, x), val)
#define bfin_read_SICB_ISR(x)		bfin_read32(__SIC_MUX(SICB_ISR0, x))
#define bfin_write_SICB_ISR(x, val)	bfin_write32(__SIC_MUX(SICB_ISR0, x), val)

#endif				/* _MACH_BLACKFIN_H_ */
