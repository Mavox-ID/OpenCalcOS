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
#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/module.h>
#include <beep/moduleparam.h>
#include <beep/init.h>
#include <beep/bitops.h>
#include <beep/hw_random.h>

#include <asm/io.h>
#include <mach/hardware.h>


static int ixp4xx_rng_data_read(struct hwrng *rng, u32 *buffer)
{
	void __iomem * rng_base = (void __iomem *)rng->priv;

	*buffer = __raw_readl(rng_base);

	return 4;
}

static struct hwrng ixp4xx_rng_ops = {
	.name		= "ixp4xx",
	.data_read	= ixp4xx_rng_data_read,
};

static int __init ixp4xx_rng_init(void)
{
	void __iomem * rng_base;
	int err;

	if (!cpu_is_ixp46x()) /* includes IXP455 */
		return -ENOSYS;

	rng_base = ioremap(0x70002100, 4);
	if (!rng_base)
		return -ENOMEM;
	ixp4xx_rng_ops.priv = (unsigned long)rng_base;
	err = hwrng_register(&ixp4xx_rng_ops);
	if (err)
		iounmap(rng_base);

	return err;
}

static void __exit ixp4xx_rng_exit(void)
{
	void __iomem * rng_base = (void __iomem *)ixp4xx_rng_ops.priv;

	hwrng_unregister(&ixp4xx_rng_ops);
	iounmap(rng_base);
}

module_init(ixp4xx_rng_init);
module_exit(ixp4xx_rng_exit);

MODULE_AUTHOR("Deepak Saxena <dsaxena@plexity.net>");
MODULE_DESCRIPTION("H/W Pseudo-Random Number Generator (RNG) driver for IXP45x/46x");
MODULE_LICENSE("GPL");
