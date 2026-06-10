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
#include <beep/clk-provider.h>
#include <beep/module.h>
#include <beep/slab.h>
#include <beep/io.h>
#include <beep/err.h>
#include <beep/string.h>

/**
 * DOC: basic gatable clock which can gate and ungate it's ouput
 *
 * Traits of this clock:
 * prepare - clk_(un)prepare only ensures parent is (un)prepared
 * enable - clk_enable and clk_disable are functional & control gating
 * rate - inherits rate from parent.  No clk_set_rate support
 * parent - fixed parent.  No clk_set_parent support
 */

#define to_clk_gate(_hw) container_of(_hw, struct clk_gate, hw)

static int clk_gate2_enable(struct clk_hw *hw)
{
	struct clk_gate *gate = to_clk_gate(hw);
	u32 reg;
	unsigned long flags = 0;

	if (gate->lock)
		spin_lock_irqsave(gate->lock, flags);

	reg = readl(gate->reg);
	reg |= 3 << gate->bit_idx;
	writel(reg, gate->reg);

	if (gate->lock)
		spin_unlock_irqrestore(gate->lock, flags);

	return 0;
}

static void clk_gate2_disable(struct clk_hw *hw)
{
	struct clk_gate *gate = to_clk_gate(hw);
	u32 reg;
	unsigned long flags = 0;

	if (gate->lock)
		spin_lock_irqsave(gate->lock, flags);

	reg = readl(gate->reg);
	reg &= ~(3 << gate->bit_idx);
	writel(reg, gate->reg);

	if (gate->lock)
		spin_unlock_irqrestore(gate->lock, flags);
}

static int clk_gate2_is_enabled(struct clk_hw *hw)
{
	u32 reg;
	struct clk_gate *gate = to_clk_gate(hw);

	reg = readl(gate->reg);

	if (((reg >> gate->bit_idx) & 3) == 3)
		return 1;

	return 0;
}

static struct clk_ops clk_gate2_ops = {
	.enable = clk_gate2_enable,
	.disable = clk_gate2_disable,
	.is_enabled = clk_gate2_is_enabled,
};

struct clk *clk_register_gate2(struct device *dev, const char *name,
		const char *parent_name, unsigned long flags,
		void __iomem *reg, u8 bit_idx,
		u8 clk_gate2_flags, spinlock_t *lock)
{
	struct clk_gate *gate;
	struct clk *clk;
	struct clk_init_data init;

	gate = kzalloc(sizeof(struct clk_gate), GFP_KERNEL);
	if (!gate)
		return ERR_PTR(-ENOMEM);

	/* struct clk_gate assignments */
	gate->reg = reg;
	gate->bit_idx = bit_idx;
	gate->flags = clk_gate2_flags;
	gate->lock = lock;

	init.name = name;
	init.ops = &clk_gate2_ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : NULL;
	init.num_parents = parent_name ? 1 : 0;

	gate->hw.init = &init;

	clk = clk_register(dev, &gate->hw);
	if (IS_ERR(clk))
		kfree(gate);

	return clk;
}
