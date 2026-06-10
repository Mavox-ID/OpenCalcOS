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
#include <beep/module.h>
#include <beep/io.h>
#include <beep/of.h>
#include <beep/of_address.h>
#include <beep/of_device.h>
#include <beep/of_platform.h>

#define SIRFSOC_CPUIOBRG_CTRL           0x00
#define SIRFSOC_CPUIOBRG_WRBE           0x04
#define SIRFSOC_CPUIOBRG_ADDR           0x08
#define SIRFSOC_CPUIOBRG_DATA           0x0c

/*
 * suspend asm codes will access this address to make system deepsleep
 * after DRAM becomes self-refresh
 */
void __iomem *sirfsoc_rtciobrg_base;
static DEFINE_SPINLOCK(rtciobrg_lock);

/*
 * symbols without lock are only used by suspend asm codes
 * and these symbols are not exported too
 */
void sirfsoc_rtc_iobrg_wait_sync(void)
{
	while (readl_relaxed(sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_CTRL))
		cpu_relax();
}

void sirfsoc_rtc_iobrg_besyncing(void)
{
	unsigned long flags;

	spin_lock_irqsave(&rtciobrg_lock, flags);

	sirfsoc_rtc_iobrg_wait_sync();

	spin_unlock_irqrestore(&rtciobrg_lock, flags);
}
EXPORT_SYMBOL_GPL(sirfsoc_rtc_iobrg_besyncing);

u32 __sirfsoc_rtc_iobrg_readl(u32 addr)
{
	sirfsoc_rtc_iobrg_wait_sync();

	writel_relaxed(0x00, sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_WRBE);
	writel_relaxed(addr, sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_ADDR);
	writel_relaxed(0x01, sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_CTRL);

	sirfsoc_rtc_iobrg_wait_sync();

	return readl_relaxed(sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_DATA);
}

u32 sirfsoc_rtc_iobrg_readl(u32 addr)
{
	unsigned long flags, val;

	spin_lock_irqsave(&rtciobrg_lock, flags);

	val = __sirfsoc_rtc_iobrg_readl(addr);

	spin_unlock_irqrestore(&rtciobrg_lock, flags);

	return val;
}
EXPORT_SYMBOL_GPL(sirfsoc_rtc_iobrg_readl);

void sirfsoc_rtc_iobrg_pre_writel(u32 val, u32 addr)
{
	sirfsoc_rtc_iobrg_wait_sync();

	writel_relaxed(0xf1, sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_WRBE);
	writel_relaxed(addr, sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_ADDR);

	writel_relaxed(val, sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_DATA);
}

void sirfsoc_rtc_iobrg_writel(u32 val, u32 addr)
{
	unsigned long flags;

	spin_lock_irqsave(&rtciobrg_lock, flags);

	sirfsoc_rtc_iobrg_pre_writel(val, addr);

	writel_relaxed(0x01, sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_CTRL);

	sirfsoc_rtc_iobrg_wait_sync();

	spin_unlock_irqrestore(&rtciobrg_lock, flags);
}
EXPORT_SYMBOL_GPL(sirfsoc_rtc_iobrg_writel);

static const struct of_device_id rtciobrg_ids[] = {
	{ .compatible = "sirf,prima2-rtciobg" },
	{}
};

static int sirfsoc_rtciobrg_probe(struct platform_device *op)
{
	struct device_node *np = op->dev.of_node;

	sirfsoc_rtciobrg_base = of_iomap(np, 0);
	if (!sirfsoc_rtciobrg_base)
		panic("unable to map rtc iobrg registers\n");

	return 0;
}

static struct platform_driver sirfsoc_rtciobrg_driver = {
	.probe		= sirfsoc_rtciobrg_probe,
	.driver = {
		.name = "sirfsoc-rtciobrg",
		.owner = THIS_MODULE,
		.of_match_table	= rtciobrg_ids,
	},
};

static int __init sirfsoc_rtciobrg_init(void)
{
	return platform_driver_register(&sirfsoc_rtciobrg_driver);
}
postcore_initcall(sirfsoc_rtciobrg_init);

MODULE_AUTHOR("Zhiwu Song <zhiwu.song@csr.com>, "
		"Barry Song <baohua.song@csr.com>");
MODULE_DESCRIPTION("CSR SiRFprimaII rtc io bridge");
MODULE_LICENSE("GPL");
