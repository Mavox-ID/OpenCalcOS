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
#ifndef _MACH_PLL_H
#define _MACH_PLL_H

#ifndef __ASSEMBLY__

#ifdef CONFIG_SMP

#include <asm/blackfin.h>
#include <asm/irqflags.h>
#include <mach/irq.h>

#define SUPPLE_0_WAKEUP ((IRQ_SUPPLE_0 - (IRQ_CORETMR + 1)) % 32)
#define SUPPLE_1_WAKEUP ((IRQ_SUPPLE_1 - (IRQ_CORETMR + 1)) % 32)

static inline void
bfin_iwr_restore(unsigned long iwr0, unsigned long iwr1, unsigned long iwr2)
{
	unsigned long SICA_SICB_OFF = ((bfin_read_DSPID() & 0xff) ? 0x1000 : 0);

	bfin_write32(SIC_IWR0 + SICA_SICB_OFF, iwr0);
	bfin_write32(SIC_IWR1 + SICA_SICB_OFF, iwr1);
}
#define bfin_iwr_restore bfin_iwr_restore

static inline void
bfin_iwr_save(unsigned long niwr0, unsigned long niwr1, unsigned long niwr2,
              unsigned long *iwr0, unsigned long *iwr1, unsigned long *iwr2)
{
	unsigned long SICA_SICB_OFF = ((bfin_read_DSPID() & 0xff) ? 0x1000 : 0);

	*iwr0 = bfin_read32(SIC_IWR0 + SICA_SICB_OFF);
	*iwr1 = bfin_read32(SIC_IWR1 + SICA_SICB_OFF);
	bfin_iwr_restore(niwr0, niwr1, niwr2);
}
#define bfin_iwr_save bfin_iwr_save

static inline void
bfin_iwr_set_sup0(unsigned long *iwr0, unsigned long *iwr1, unsigned long *iwr2)
{
	bfin_iwr_save(0, IWR_ENABLE(SUPPLE_0_WAKEUP) |
			IWR_ENABLE(SUPPLE_1_WAKEUP), 0, iwr0, iwr1, iwr2);
}

#endif

#endif

#include <mach-common/pll.h>

#endif
