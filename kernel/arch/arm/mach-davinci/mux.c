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
#include <beep/module.h>
#include <beep/spinlock.h>

#include <mach/mux.h>
#include <mach/common.h>

static void __iomem *pinmux_base;

/*
 * Sets the DAVINCI MUX register based on the table
 */
int __init_or_module davinci_cfg_reg(const unsigned long index)
{
	static DEFINE_SPINLOCK(mux_spin_lock);
	struct davinci_soc_info *soc_info = &davinci_soc_info;
	unsigned long flags;
	const struct mux_config *cfg;
	unsigned int reg_orig = 0, reg = 0;
	unsigned int mask, warn = 0;

	if (WARN_ON(!soc_info->pinmux_pins))
		return -ENODEV;

	if (!pinmux_base) {
		pinmux_base = ioremap(soc_info->pinmux_base, SZ_4K);
		if (WARN_ON(!pinmux_base))
			return -ENOMEM;
	}

	if (index >= soc_info->pinmux_pins_num) {
		printk(KERN_ERR "Invalid pin mux index: %lu (%lu)\n",
		       index, soc_info->pinmux_pins_num);
		dump_stack();
		return -ENODEV;
	}

	cfg = &soc_info->pinmux_pins[index];

	if (cfg->name == NULL) {
		printk(KERN_ERR "No entry for the specified index\n");
		return -ENODEV;
	}

	/* Update the mux register in question */
	if (cfg->mask) {
		unsigned	tmp1, tmp2;

		spin_lock_irqsave(&mux_spin_lock, flags);
		reg_orig = __raw_readl(pinmux_base + cfg->mux_reg);

		mask = (cfg->mask << cfg->mask_offset);
		tmp1 = reg_orig & mask;
		reg = reg_orig & ~mask;

		tmp2 = (cfg->mode << cfg->mask_offset);
		reg |= tmp2;

		if (tmp1 != tmp2)
			warn = 1;

		__raw_writel(reg, pinmux_base + cfg->mux_reg);
		spin_unlock_irqrestore(&mux_spin_lock, flags);
	}

	if (warn) {
#ifdef CONFIG_DAVINCI_MUX_WARNINGS
		printk(KERN_WARNING "MUX: initialized %s\n", cfg->name);
#endif
	}

#ifdef CONFIG_DAVINCI_MUX_DEBUG
	if (cfg->debug || warn) {
		printk(KERN_WARNING "MUX: Setting register %s\n", cfg->name);
		printk(KERN_WARNING "	   %s (0x%08x) = 0x%08x -> 0x%08x\n",
		       cfg->mux_reg_name, cfg->mux_reg, reg_orig, reg);
	}
#endif

	return 0;
}
EXPORT_SYMBOL(davinci_cfg_reg);

int __init_or_module davinci_cfg_reg_list(const short pins[])
{
	int i, error = -EINVAL;

	if (pins)
		for (i = 0; pins[i] >= 0; i++) {
			error = davinci_cfg_reg(pins[i]);
			if (error)
				break;
		}

	return error;
}
