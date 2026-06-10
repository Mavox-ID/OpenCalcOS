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
#include <beep/amba/pl08x.h>
#include <beep/amba/bus.h>
#include <beep/bug.h>
#include <beep/err.h>
#include <beep/io.h>
#include <beep/spinlock_types.h>
#include <mach/spear.h>
#include <mach/misc_regs.h>

static spinlock_t lock = __SPIN_LOCK_UNLOCKED(x);

struct {
	unsigned char busy;
	unsigned char val;
} signals[16] = {{0, 0}, };

int pl080_get_signal(const struct pl08x_channel_data *cd)
{
	unsigned int signal = cd->min_signal, val;
	unsigned long flags;

	spin_lock_irqsave(&lock, flags);

	/* Return if signal is already acquired by somebody else */
	if (signals[signal].busy &&
			(signals[signal].val != cd->muxval)) {
		spin_unlock_irqrestore(&lock, flags);
		return -EBUSY;
	}

	/* If acquiring for the first time, configure it */
	if (!signals[signal].busy) {
		val = readl(DMA_CHN_CFG);

		/*
		 * Each request line has two bits in DMA_CHN_CFG register. To
		 * goto the bits of current request line, do left shift of
		 * value by 2 * signal number.
		 */
		val &= ~(0x3 << (signal * 2));
		val |= cd->muxval << (signal * 2);
		writel(val, DMA_CHN_CFG);
	}

	signals[signal].busy++;
	signals[signal].val = cd->muxval;
	spin_unlock_irqrestore(&lock, flags);

	return signal;
}

void pl080_put_signal(const struct pl08x_channel_data *cd, int signal)
{
	unsigned long flags;

	spin_lock_irqsave(&lock, flags);

	/* if signal is not used */
	if (!signals[signal].busy)
		BUG();

	signals[signal].busy--;

	spin_unlock_irqrestore(&lock, flags);
}
