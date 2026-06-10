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
#include <beep/module.h>
#include <beep/spinlock.h>
#include <asm/mach-au1x00/au1000.h>

#define VSS_GATE	0x00	/* gate wait timers */
#define VSS_CLKRST	0x04	/* clock/block control */
#define VSS_FTR		0x08	/* footers */

#define VSS_ADDR(blk)	(KSEG1ADDR(AU1300_VSS_PHYS_ADDR) + (blk * 0x0c))

static DEFINE_SPINLOCK(au1300_vss_lock);

/* enable a block as outlined in the databook */
static inline void __enable_block(int block)
{
	void __iomem *base = (void __iomem *)VSS_ADDR(block);

	__raw_writel(3, base + VSS_CLKRST);	/* enable clock, assert reset */
	wmb();

	__raw_writel(0x01fffffe, base + VSS_GATE); /* maximum setup time */
	wmb();

	/* enable footers in sequence */
	__raw_writel(0x01, base + VSS_FTR);
	wmb();
	__raw_writel(0x03, base + VSS_FTR);
	wmb();
	__raw_writel(0x07, base + VSS_FTR);
	wmb();
	__raw_writel(0x0f, base + VSS_FTR);
	wmb();

	__raw_writel(0x01ffffff, base + VSS_GATE); /* start FSM too */
	wmb();

	__raw_writel(2, base + VSS_CLKRST);	/* deassert reset */
	wmb();

	__raw_writel(0x1f, base + VSS_FTR);	/* enable isolation cells */
	wmb();
}

/* disable a block as outlined in the databook */
static inline void __disable_block(int block)
{
	void __iomem *base = (void __iomem *)VSS_ADDR(block);

	__raw_writel(0x0f, base + VSS_FTR);	/* disable isolation cells */
	wmb();
	__raw_writel(0, base + VSS_GATE);	/* disable FSM */
	wmb();
	__raw_writel(3, base + VSS_CLKRST);	/* assert reset */
	wmb();
	__raw_writel(1, base + VSS_CLKRST);	/* disable clock */
	wmb();
	__raw_writel(0, base + VSS_FTR);	/* disable all footers */
	wmb();
}

void au1300_vss_block_control(int block, int enable)
{
	unsigned long flags;

	if (alchemy_get_cputype() != ALCHEMY_CPU_AU1300)
		return;

	/* only one block at a time */
	spin_lock_irqsave(&au1300_vss_lock, flags);
	if (enable)
		__enable_block(block);
	else
		__disable_block(block);
	spin_unlock_irqrestore(&au1300_vss_lock, flags);
}
EXPORT_SYMBOL_GPL(au1300_vss_block_control);
