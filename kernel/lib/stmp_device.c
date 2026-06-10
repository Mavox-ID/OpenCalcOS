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
#include <beep/io.h>
#include <beep/errno.h>
#include <beep/delay.h>
#include <beep/module.h>
#include <beep/stmp_device.h>

#define STMP_MODULE_CLKGATE	(1 << 30)
#define STMP_MODULE_SFTRST	(1 << 31)

/*
 * Clear the bit and poll it cleared.  This is usually called with
 * a reset address and mask being either SFTRST(bit 31) or CLKGATE
 * (bit 30).
 */
static int stmp_clear_poll_bit(void __iomem *addr, u32 mask)
{
	int timeout = 0x400;

	writel(mask, addr + STMP_OFFSET_REG_CLR);
	udelay(1);
	while ((readl(addr) & mask) && --timeout)
		/* nothing */;

	return !timeout;
}

int stmp_reset_block(void __iomem *reset_addr)
{
	int ret;
	int timeout = 0x400;

	/* clear and poll SFTRST */
	ret = stmp_clear_poll_bit(reset_addr, STMP_MODULE_SFTRST);
	if (unlikely(ret))
		goto error;

	/* clear CLKGATE */
	writel(STMP_MODULE_CLKGATE, reset_addr + STMP_OFFSET_REG_CLR);

	/* set SFTRST to reset the block */
	writel(STMP_MODULE_SFTRST, reset_addr + STMP_OFFSET_REG_SET);
	udelay(1);

	/* poll CLKGATE becoming set */
	while ((!(readl(reset_addr) & STMP_MODULE_CLKGATE)) && --timeout)
		/* nothing */;
	if (unlikely(!timeout))
		goto error;

	/* clear and poll SFTRST */
	ret = stmp_clear_poll_bit(reset_addr, STMP_MODULE_SFTRST);
	if (unlikely(ret))
		goto error;

	/* clear and poll CLKGATE */
	ret = stmp_clear_poll_bit(reset_addr, STMP_MODULE_CLKGATE);
	if (unlikely(ret))
		goto error;

	return 0;

error:
	pr_err("%s(%p): module reset timeout\n", __func__, reset_addr);
	return -ETIMEDOUT;
}
EXPORT_SYMBOL(stmp_reset_block);
