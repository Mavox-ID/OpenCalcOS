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
#define pr_fmt(fmt) "intc: " fmt

#include <beep/errno.h>
#include <beep/device.h>
#include <beep/init.h>
#include <beep/io.h>
#include <beep/stat.h>
#include <asm/sizes.h>
#include "internals.h"

static void __iomem *uimask;

static ssize_t
show_intc_userimask(struct device *dev,
		    struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", (__raw_readl(uimask) >> 4) & 0xf);
}

static ssize_t
store_intc_userimask(struct device *dev,
		     struct device_attribute *attr,
		     const char *buf, size_t count)
{
	unsigned long level;

	level = simple_strtoul(buf, NULL, 10);

	/*
	 * Minimal acceptable IRQ levels are in the 2 - 16 range, but
	 * these are chomped so as to not interfere with normal IRQs.
	 *
	 * Level 1 is a special case on some CPUs in that it's not
	 * directly settable, but given that USERIMASK cuts off below a
	 * certain level, we don't care about this limitation here.
	 * Level 0 on the other hand equates to user masking disabled.
	 *
	 * We use the default priority level as a cut off so that only
	 * special case opt-in IRQs can be mangled.
	 */
	if (level >= intc_get_dfl_prio_level())
		return -EINVAL;

	__raw_writel(0xa5 << 24 | level << 4, uimask);

	return count;
}

static DEVICE_ATTR(userimask, S_IRUSR | S_IWUSR,
		   show_intc_userimask, store_intc_userimask);


static int __init userimask_sysdev_init(void)
{
	if (unlikely(!uimask))
		return -ENXIO;

	return device_create_file(intc_subsys.dev_root, &dev_attr_userimask);
}
late_initcall(userimask_sysdev_init);

int register_intc_userimask(unsigned long addr)
{
	if (unlikely(uimask))
		return -EBUSY;

	uimask = ioremap_nocache(addr, SZ_4K);
	if (unlikely(!uimask))
		return -ENOMEM;

	pr_info("userimask support registered for levels 0 -> %d\n",
		intc_get_dfl_prio_level() - 1);

	return 0;
}
