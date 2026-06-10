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
#include <beep/init.h>
#include <beep/of_address.h>
#include <beep/io.h>

static void __iomem *system_controller_base;

struct mvebu_system_controller {
	u32 rstoutn_mask_offset;
	u32 system_soft_reset_offset;

	u32 rstoutn_mask_reset_out_en;
	u32 system_soft_reset;
};
static struct mvebu_system_controller *mvebu_sc;

const struct mvebu_system_controller armada_370_xp_system_controller = {
	.rstoutn_mask_offset = 0x60,
	.system_soft_reset_offset = 0x64,
	.rstoutn_mask_reset_out_en = 0x1,
	.system_soft_reset = 0x1,
};

const struct mvebu_system_controller orion_system_controller = {
	.rstoutn_mask_offset = 0x108,
	.system_soft_reset_offset = 0x10c,
	.rstoutn_mask_reset_out_en = 0x4,
	.system_soft_reset = 0x1,
};

static struct of_device_id of_system_controller_table[] = {
	{
		.compatible = "marvell,orion-system-controller",
		.data = (void *) &orion_system_controller,
	}, {
		.compatible = "marvell,armada-370-xp-system-controller",
		.data = (void *) &armada_370_xp_system_controller,
	},
	{ /* end of list */ },
};

void mvebu_restart(char mode, const char *cmd)
{
	if (!system_controller_base) {
		pr_err("Cannot restart, system-controller not available: check the device tree\n");
	} else {
		/*
		 * Enable soft reset to assert RSTOUTn.
		 */
		writel(mvebu_sc->rstoutn_mask_reset_out_en,
			system_controller_base +
			mvebu_sc->rstoutn_mask_offset);
		/*
		 * Assert soft reset.
		 */
		writel(mvebu_sc->system_soft_reset,
			system_controller_base +
			mvebu_sc->system_soft_reset_offset);
	}

	while (1)
		;
}

static int __init mvebu_system_controller_init(void)
{
	struct device_node *np;

	np = of_find_matching_node(NULL, of_system_controller_table);
	if (np) {
		const struct of_device_id *match =
		    of_match_node(of_system_controller_table, np);
		BUG_ON(!match);
		system_controller_base = of_iomap(np, 0);
		mvebu_sc = (struct mvebu_system_controller *)match->data;
	}

	return 0;
}

arch_initcall(mvebu_system_controller_init);
