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
#ifndef _MACH_COMMON_PLL_H
#define _MACH_COMMON_PLL_H

#ifndef __ASSEMBLY__

#include <asm/blackfin.h>
#include <asm/irqflags.h>

#ifndef bfin_iwr_restore
static inline void
bfin_iwr_restore(unsigned long iwr0, unsigned long iwr1, unsigned long iwr2)
{
#ifdef SIC_IWR
	bfin_write_SIC_IWR(iwr0);
#else
	bfin_write_SIC_IWR0(iwr0);
# ifdef SIC_IWR1
	bfin_write_SIC_IWR1(iwr1);
# endif
# ifdef SIC_IWR2
	bfin_write_SIC_IWR2(iwr2);
# endif
#endif
}
#endif

#ifndef bfin_iwr_save
static inline void
bfin_iwr_save(unsigned long niwr0, unsigned long niwr1, unsigned long niwr2,
              unsigned long *iwr0, unsigned long *iwr1, unsigned long *iwr2)
{
#ifdef SIC_IWR
	*iwr0 = bfin_read_SIC_IWR();
#else
	*iwr0 = bfin_read_SIC_IWR0();
# ifdef SIC_IWR1
	*iwr1 = bfin_read_SIC_IWR1();
# endif
# ifdef SIC_IWR2
	*iwr2 = bfin_read_SIC_IWR2();
# endif
#endif
	bfin_iwr_restore(niwr0, niwr1, niwr2);
}
#endif

static inline void _bfin_write_pll_relock(u32 addr, unsigned int val)
{
	unsigned long flags, iwr0, iwr1, iwr2;

	if (val == bfin_read_PLL_CTL())
		return;

	flags = hard_local_irq_save();
	/* Enable the PLL Wakeup bit in SIC IWR */
	bfin_iwr_save(IWR_ENABLE(0), 0, 0, &iwr0, &iwr1, &iwr2);

	bfin_write16(addr, val);
	SSYNC();
	asm("IDLE;");

	bfin_iwr_restore(iwr0, iwr1, iwr2);
	hard_local_irq_restore(flags);
}

/* Writing to PLL_CTL initiates a PLL relock sequence */
static inline void bfin_write_PLL_CTL(unsigned int val)
{
	_bfin_write_pll_relock(PLL_CTL, val);
}

/* Writing to VR_CTL initiates a PLL relock sequence */
static inline void bfin_write_VR_CTL(unsigned int val)
{
	_bfin_write_pll_relock(VR_CTL, val);
}

#endif

#endif
