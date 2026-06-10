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
#include <beep/bitops.h>
#include <beep/io.h>
#include <beep/clk.h>
#include <beep/clkdev.h>
#include <beep/clk-provider.h>
#include <beep/clk/mvebu.h>
#include <beep/of.h>
#include <beep/of_address.h>

struct mvebu_gating_ctrl {
	spinlock_t lock;
	struct clk **gates;
	int num_gates;
};

struct mvebu_soc_descr {
	const char *name;
	const char *parent;
	int bit_idx;
};

#define to_clk_gate(_hw) container_of(_hw, struct clk_gate, hw)

static struct clk *mvebu_clk_gating_get_src(
	struct of_phandle_args *clkspec, void *data)
{
	struct mvebu_gating_ctrl *ctrl = (struct mvebu_gating_ctrl *)data;
	int n;

	if (clkspec->args_count < 1)
		return ERR_PTR(-EINVAL);

	for (n = 0; n < ctrl->num_gates; n++) {
		struct clk_gate *gate =
			to_clk_gate(__clk_get_hw(ctrl->gates[n]));
		if (clkspec->args[0] == gate->bit_idx)
			return ctrl->gates[n];
	}
	return ERR_PTR(-ENODEV);
}

static void __init mvebu_clk_gating_setup(
	struct device_node *np, const struct mvebu_soc_descr *descr)
{
	struct mvebu_gating_ctrl *ctrl;
	struct clk *clk;
	void __iomem *base;
	const char *default_parent = NULL;
	int n;

	base = of_iomap(np, 0);

	clk = of_clk_get(np, 0);
	if (!IS_ERR(clk)) {
		default_parent = __clk_get_name(clk);
		clk_put(clk);
	}

	ctrl = kzalloc(sizeof(struct mvebu_gating_ctrl), GFP_KERNEL);
	if (WARN_ON(!ctrl))
		return;

	spin_lock_init(&ctrl->lock);

	/*
	 * Count, allocate, and register clock gates
	 */
	for (n = 0; descr[n].name;)
		n++;

	ctrl->num_gates = n;
	ctrl->gates = kzalloc(ctrl->num_gates * sizeof(struct clk *),
			      GFP_KERNEL);
	if (WARN_ON(!ctrl->gates)) {
		kfree(ctrl);
		return;
	}

	for (n = 0; n < ctrl->num_gates; n++) {
		u8 flags = 0;
		const char *parent =
			(descr[n].parent) ? descr[n].parent : default_parent;

		/*
		 * On Armada 370, the DDR clock is a special case: it
		 * isn't taken by any driver, but should anyway be
		 * kept enabled, so we mark it as IGNORE_UNUSED for
		 * now.
		 */
		if (!strcmp(descr[n].name, "ddr"))
			flags |= CLK_IGNORE_UNUSED;

		ctrl->gates[n] = clk_register_gate(NULL, descr[n].name, parent,
				   flags, base, descr[n].bit_idx, 0, &ctrl->lock);
		WARN_ON(IS_ERR(ctrl->gates[n]));
	}
	of_clk_add_provider(np, mvebu_clk_gating_get_src, ctrl);
}

/*
 * SoC specific clock gating control
 */

#ifdef CONFIG_MACH_ARMADA_370
static const struct mvebu_soc_descr __initconst armada_370_gating_descr[] = {
	{ "audio", NULL, 0 },
	{ "pex0_en", NULL, 1 },
	{ "pex1_en", NULL,  2 },
	{ "ge1", NULL, 3 },
	{ "ge0", NULL, 4 },
	{ "pex0", NULL, 5 },
	{ "pex1", NULL, 9 },
	{ "sata0", NULL, 15 },
	{ "sdio", NULL, 17 },
	{ "tdm", NULL, 25 },
	{ "ddr", NULL, 28 },
	{ "sata1", NULL, 30 },
	{ }
};
#endif

#ifdef CONFIG_MACH_ARMADA_XP
static const struct mvebu_soc_descr __initconst armada_xp_gating_descr[] = {
	{ "audio", NULL, 0 },
	{ "ge3", NULL, 1 },
	{ "ge2", NULL,  2 },
	{ "ge1", NULL, 3 },
	{ "ge0", NULL, 4 },
	{ "pex0", NULL, 5 },
	{ "pex1", NULL, 6 },
	{ "pex2", NULL, 7 },
	{ "pex3", NULL, 8 },
	{ "bp", NULL, 13 },
	{ "sata0lnk", NULL, 14 },
	{ "sata0", "sata0lnk", 15 },
	{ "lcd", NULL, 16 },
	{ "sdio", NULL, 17 },
	{ "usb0", NULL, 18 },
	{ "usb1", NULL, 19 },
	{ "usb2", NULL, 20 },
	{ "xor0", NULL, 22 },
	{ "crypto", NULL, 23 },
	{ "tdm", NULL, 25 },
	{ "xor1", NULL, 28 },
	{ "sata1lnk", NULL, 29 },
	{ "sata1", "sata1lnk", 30 },
	{ }
};
#endif

#ifdef CONFIG_ARCH_DOVE
static const struct mvebu_soc_descr __initconst dove_gating_descr[] = {
	{ "usb0", NULL, 0 },
	{ "usb1", NULL, 1 },
	{ "ge", "gephy", 2 },
	{ "sata", NULL, 3 },
	{ "pex0", NULL, 4 },
	{ "pex1", NULL, 5 },
	{ "sdio0", NULL, 8 },
	{ "sdio1", NULL, 9 },
	{ "nand", NULL, 10 },
	{ "camera", NULL, 11 },
	{ "i2s0", NULL, 12 },
	{ "i2s1", NULL, 13 },
	{ "crypto", NULL, 15 },
	{ "ac97", NULL, 21 },
	{ "pdma", NULL, 22 },
	{ "xor0", NULL, 23 },
	{ "xor1", NULL, 24 },
	{ "gephy", NULL, 30 },
	{ }
};
#endif

#ifdef CONFIG_ARCH_KIRKWOOD
static const struct mvebu_soc_descr __initconst kirkwood_gating_descr[] = {
	{ "ge0", NULL, 0 },
	{ "pex0", NULL, 2 },
	{ "usb0", NULL, 3 },
	{ "sdio", NULL, 4 },
	{ "tsu", NULL, 5 },
	{ "runit", NULL, 7 },
	{ "xor0", NULL, 8 },
	{ "audio", NULL, 9 },
	{ "sata0", NULL, 14 },
	{ "sata1", NULL, 15 },
	{ "xor1", NULL, 16 },
	{ "crypto", NULL, 17 },
	{ "pex1", NULL, 18 },
	{ "ge1", NULL, 19 },
	{ "tdm", NULL, 20 },
	{ }
};
#endif

static const __initdata struct of_device_id clk_gating_match[] = {
#ifdef CONFIG_MACH_ARMADA_370
	{
		.compatible = "marvell,armada-370-gating-clock",
		.data = armada_370_gating_descr,
	},
#endif

#ifdef CONFIG_MACH_ARMADA_XP
	{
		.compatible = "marvell,armada-xp-gating-clock",
		.data = armada_xp_gating_descr,
	},
#endif

#ifdef CONFIG_ARCH_DOVE
	{
		.compatible = "marvell,dove-gating-clock",
		.data = dove_gating_descr,
	},
#endif

#ifdef CONFIG_ARCH_KIRKWOOD
	{
		.compatible = "marvell,kirkwood-gating-clock",
		.data = kirkwood_gating_descr,
	},
#endif

	{ }
};

void __init mvebu_gating_clk_init(void)
{
	struct device_node *np;

	for_each_matching_node(np, clk_gating_match) {
		const struct of_device_id *match =
			of_match_node(clk_gating_match, np);
		mvebu_clk_gating_setup(np,
		       (const struct mvebu_soc_descr *)match->data);
	}
}
