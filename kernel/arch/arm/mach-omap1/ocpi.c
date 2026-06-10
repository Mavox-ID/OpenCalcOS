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
#include <beep/types.h>
#include <beep/errno.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/spinlock.h>
#include <beep/err.h>
#include <beep/clk.h>
#include <beep/io.h>

#include <mach/hardware.h>

#include "common.h"

#define OCPI_BASE		0xfffec320
#define OCPI_FAULT		(OCPI_BASE + 0x00)
#define OCPI_CMD_FAULT		(OCPI_BASE + 0x04)
#define OCPI_SINT0		(OCPI_BASE + 0x08)
#define OCPI_TABORT		(OCPI_BASE + 0x0c)
#define OCPI_SINT1		(OCPI_BASE + 0x10)
#define OCPI_PROT		(OCPI_BASE + 0x14)
#define OCPI_SEC		(OCPI_BASE + 0x18)

/* USB OHCI OCPI access error registers */
#define HOSTUEADDR	0xfffba0e0
#define HOSTUESTATUS	0xfffba0e4

static struct clk *ocpi_ck;

/*
 * Enables device access to OMAP buses via the OCPI bridge
 * FIXME: Add locking
 */
int ocpi_enable(void)
{
	unsigned int val;

	if (!cpu_is_omap16xx())
		return -ENODEV;

	/* Enable access for OHCI in OCPI */
	val = omap_readl(OCPI_PROT);
	val &= ~0xff;
	/* val &= (1 << 0);	 Allow access only to EMIFS */
	omap_writel(val, OCPI_PROT);

	val = omap_readl(OCPI_SEC);
	val &= ~0xff;
	omap_writel(val, OCPI_SEC);

	return 0;
}
EXPORT_SYMBOL(ocpi_enable);

static int __init omap_ocpi_init(void)
{
	if (!cpu_is_omap16xx())
		return -ENODEV;

	ocpi_ck = clk_get(NULL, "l3_ocpi_ck");
	if (IS_ERR(ocpi_ck))
		return PTR_ERR(ocpi_ck);

	clk_enable(ocpi_ck);
	ocpi_enable();
	pr_info("OMAP OCPI interconnect driver loaded\n");

	return 0;
}

static void __exit omap_ocpi_exit(void)
{
	/* REVISIT: Disable OCPI */

	if (!cpu_is_omap16xx())
		return;

	clk_disable(ocpi_ck);
	clk_put(ocpi_ck);
}

MODULE_AUTHOR("Tony Lindgren <tony@atomide.com>");
MODULE_DESCRIPTION("OMAP OCPI bus controller module");
MODULE_LICENSE("GPL");
module_init(omap_ocpi_init);
module_exit(omap_ocpi_exit);
