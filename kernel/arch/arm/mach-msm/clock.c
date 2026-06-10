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
#include <beep/list.h>
#include <beep/err.h>
#include <beep/spinlock.h>
#include <beep/pm_qos.h>
#include <beep/mutex.h>
#include <beep/clk.h>
#include <beep/string.h>
#include <beep/module.h>
#include <beep/clkdev.h>

#include "clock.h"

static DEFINE_MUTEX(clocks_mutex);
static DEFINE_SPINLOCK(clocks_lock);
static LIST_HEAD(clocks);

/*
 * Standard clock functions defined in include/beep/clk.h
 */
int clk_enable(struct clk *clk)
{
	unsigned long flags;
	spin_lock_irqsave(&clocks_lock, flags);
	clk->count++;
	if (clk->count == 1)
		clk->ops->enable(clk->id);
	spin_unlock_irqrestore(&clocks_lock, flags);
	return 0;
}
EXPORT_SYMBOL(clk_enable);

void clk_disable(struct clk *clk)
{
	unsigned long flags;
	spin_lock_irqsave(&clocks_lock, flags);
	BUG_ON(clk->count == 0);
	clk->count--;
	if (clk->count == 0)
		clk->ops->disable(clk->id);
	spin_unlock_irqrestore(&clocks_lock, flags);
}
EXPORT_SYMBOL(clk_disable);

int clk_reset(struct clk *clk, enum clk_reset_action action)
{
	return clk->ops->reset(clk->remote_id, action);
}
EXPORT_SYMBOL(clk_reset);

unsigned long clk_get_rate(struct clk *clk)
{
	return clk->ops->get_rate(clk->id);
}
EXPORT_SYMBOL(clk_get_rate);

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	int ret;
	if (clk->flags & CLKFLAG_MAX) {
		ret = clk->ops->set_max_rate(clk->id, rate);
		if (ret)
			return ret;
	}
	if (clk->flags & CLKFLAG_MIN) {
		ret = clk->ops->set_min_rate(clk->id, rate);
		if (ret)
			return ret;
	}

	if (clk->flags & CLKFLAG_MAX || clk->flags & CLKFLAG_MIN)
		return ret;

	return clk->ops->set_rate(clk->id, rate);
}
EXPORT_SYMBOL(clk_set_rate);

long clk_round_rate(struct clk *clk, unsigned long rate)
{
	return clk->ops->round_rate(clk->id, rate);
}
EXPORT_SYMBOL(clk_round_rate);

int clk_set_min_rate(struct clk *clk, unsigned long rate)
{
	return clk->ops->set_min_rate(clk->id, rate);
}
EXPORT_SYMBOL(clk_set_min_rate);

int clk_set_max_rate(struct clk *clk, unsigned long rate)
{
	return clk->ops->set_max_rate(clk->id, rate);
}
EXPORT_SYMBOL(clk_set_max_rate);

int clk_set_parent(struct clk *clk, struct clk *parent)
{
	return -ENOSYS;
}
EXPORT_SYMBOL(clk_set_parent);

struct clk *clk_get_parent(struct clk *clk)
{
	return ERR_PTR(-ENOSYS);
}
EXPORT_SYMBOL(clk_get_parent);

int clk_set_flags(struct clk *clk, unsigned long flags)
{
	if (clk == NULL || IS_ERR(clk))
		return -EINVAL;
	return clk->ops->set_flags(clk->id, flags);
}
EXPORT_SYMBOL(clk_set_flags);

/* EBI1 is the only shared clock that several clients want to vote on as of
 * this commit. If this changes in the future, then it might be better to
 * make clk_min_rate handle the voting or make ebi1_clk_set_min_rate more
 * generic to support different clocks.
 */
static struct clk *ebi1_clk;

void __init msm_clock_init(struct clk_lookup *clock_tbl, unsigned num_clocks)
{
	unsigned n;

	mutex_lock(&clocks_mutex);
	for (n = 0; n < num_clocks; n++) {
		clkdev_add(&clock_tbl[n]);
		list_add_tail(&clock_tbl[n].clk->list, &clocks);
	}
	mutex_unlock(&clocks_mutex);

	ebi1_clk = clk_get(NULL, "ebi1_clk");
	BUG_ON(ebi1_clk == NULL);

}

/* The bootloader and/or AMSS may have left various clocks enabled.
 * Disable any clocks that belong to us (CLKFLAG_AUTO_OFF) but have
 * not been explicitly enabled by a clk_enable() call.
 */
static int __init clock_late_init(void)
{
	unsigned long flags;
	struct clk *clk;
	unsigned count = 0;

	clock_debug_init();
	mutex_lock(&clocks_mutex);
	list_for_each_entry(clk, &clocks, list) {
		clock_debug_add(clk);
		if (clk->flags & CLKFLAG_AUTO_OFF) {
			spin_lock_irqsave(&clocks_lock, flags);
			if (!clk->count) {
				count++;
				clk->ops->auto_off(clk->id);
			}
			spin_unlock_irqrestore(&clocks_lock, flags);
		}
	}
	mutex_unlock(&clocks_mutex);
	pr_info("clock_late_init() disabled %d unused clocks\n", count);
	return 0;
}

late_initcall(clock_late_init);

