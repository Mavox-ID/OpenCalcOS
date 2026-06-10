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
#define pr_fmt(fmt) "clk-frac-synth: " fmt

#include <beep/clk-provider.h>
#include <beep/slab.h>
#include <beep/io.h>
#include <beep/err.h>
#include "clk.h"

#define DIV_FACTOR_MASK		0x1FFFF

/*
 * DOC: Fractional Synthesizer clock
 *
 * Fout from synthesizer can be given from below equation:
 *
 * Fout= Fin/2*div (division factor)
 * div is 17 bits:-
 *	0-13 (fractional part)
 *	14-16 (integer part)
 *	div is (16-14 bits).(13-0 bits) (in binary)
 *
 *	Fout = Fin/(2 * div)
 *	Fout = ((Fin / 10000)/(2 * div)) * 10000
 *	Fout = (2^14 * (Fin / 10000)/(2^14 * (2 * div))) * 10000
 *	Fout = (((Fin / 10000) << 14)/(2 * (div << 14))) * 10000
 *
 * div << 14 simply 17 bit value written at register.
 * Max error due to scaling down by 10000 is 10 KHz
 */

#define to_clk_frac(_hw) container_of(_hw, struct clk_frac, hw)

static unsigned long frac_calc_rate(struct clk_hw *hw, unsigned long prate,
		int index)
{
	struct clk_frac *frac = to_clk_frac(hw);
	struct frac_rate_tbl *rtbl = frac->rtbl;

	prate /= 10000;
	prate <<= 14;
	prate /= (2 * rtbl[index].div);
	prate *= 10000;

	return prate;
}

static long clk_frac_round_rate(struct clk_hw *hw, unsigned long drate,
		unsigned long *prate)
{
	struct clk_frac *frac = to_clk_frac(hw);
	int unused;

	return clk_round_rate_index(hw, drate, *prate, frac_calc_rate,
			frac->rtbl_cnt, &unused);
}

static unsigned long clk_frac_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct clk_frac *frac = to_clk_frac(hw);
	unsigned long flags = 0;
	unsigned int div = 1, val;

	if (frac->lock)
		spin_lock_irqsave(frac->lock, flags);

	val = readl_relaxed(frac->reg);

	if (frac->lock)
		spin_unlock_irqrestore(frac->lock, flags);

	div = val & DIV_FACTOR_MASK;

	if (!div)
		return 0;

	parent_rate = parent_rate / 10000;

	parent_rate = (parent_rate << 14) / (2 * div);
	return parent_rate * 10000;
}

/* Configures new clock rate of frac */
static int clk_frac_set_rate(struct clk_hw *hw, unsigned long drate,
				unsigned long prate)
{
	struct clk_frac *frac = to_clk_frac(hw);
	struct frac_rate_tbl *rtbl = frac->rtbl;
	unsigned long flags = 0, val;
	int i;

	clk_round_rate_index(hw, drate, prate, frac_calc_rate, frac->rtbl_cnt,
			&i);

	if (frac->lock)
		spin_lock_irqsave(frac->lock, flags);

	val = readl_relaxed(frac->reg) & ~DIV_FACTOR_MASK;
	val |= rtbl[i].div & DIV_FACTOR_MASK;
	writel_relaxed(val, frac->reg);

	if (frac->lock)
		spin_unlock_irqrestore(frac->lock, flags);

	return 0;
}

struct clk_ops clk_frac_ops = {
	.recalc_rate = clk_frac_recalc_rate,
	.round_rate = clk_frac_round_rate,
	.set_rate = clk_frac_set_rate,
};

struct clk *clk_register_frac(const char *name, const char *parent_name,
		unsigned long flags, void __iomem *reg,
		struct frac_rate_tbl *rtbl, u8 rtbl_cnt, spinlock_t *lock)
{
	struct clk_init_data init;
	struct clk_frac *frac;
	struct clk *clk;

	if (!name || !parent_name || !reg || !rtbl || !rtbl_cnt) {
		pr_err("Invalid arguments passed");
		return ERR_PTR(-EINVAL);
	}

	frac = kzalloc(sizeof(*frac), GFP_KERNEL);
	if (!frac) {
		pr_err("could not allocate frac clk\n");
		return ERR_PTR(-ENOMEM);
	}

	/* struct clk_frac assignments */
	frac->reg = reg;
	frac->rtbl = rtbl;
	frac->rtbl_cnt = rtbl_cnt;
	frac->lock = lock;
	frac->hw.init = &init;

	init.name = name;
	init.ops = &clk_frac_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	clk = clk_register(NULL, &frac->hw);
	if (!IS_ERR_OR_NULL(clk))
		return clk;

	pr_err("clk register failed\n");
	kfree(frac);

	return NULL;
}
