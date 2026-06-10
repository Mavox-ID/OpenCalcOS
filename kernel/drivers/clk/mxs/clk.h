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
#ifndef __MXS_CLK_H
#define __MXS_CLK_H

#include <beep/clk.h>
#include <beep/clk-provider.h>
#include <beep/spinlock.h>

#define SET	0x4
#define CLR	0x8

extern spinlock_t mxs_lock;

int mxs_clk_wait(void __iomem *reg, u8 shift);

struct clk *mxs_clk_pll(const char *name, const char *parent_name,
			void __iomem *base, u8 power, unsigned long rate);

struct clk *mxs_clk_ref(const char *name, const char *parent_name,
			void __iomem *reg, u8 idx);

struct clk *mxs_clk_div(const char *name, const char *parent_name,
			void __iomem *reg, u8 shift, u8 width, u8 busy);

struct clk *mxs_clk_frac(const char *name, const char *parent_name,
			 void __iomem *reg, u8 shift, u8 width, u8 busy);

static inline struct clk *mxs_clk_fixed(const char *name, int rate)
{
	return clk_register_fixed_rate(NULL, name, NULL, CLK_IS_ROOT, rate);
}

static inline struct clk *mxs_clk_gate(const char *name,
			const char *parent_name, void __iomem *reg, u8 shift)
{
	return clk_register_gate(NULL, name, parent_name, CLK_SET_RATE_PARENT,
				 reg, shift, CLK_GATE_SET_TO_DISABLE,
				 &mxs_lock);
}

static inline struct clk *mxs_clk_mux(const char *name, void __iomem *reg,
		u8 shift, u8 width, const char **parent_names, int num_parents)
{
	return clk_register_mux(NULL, name, parent_names, num_parents,
				CLK_SET_RATE_PARENT, reg, shift, width,
				0, &mxs_lock);
}

static inline struct clk *mxs_clk_fixed_factor(const char *name,
		const char *parent_name, unsigned int mult, unsigned int div)
{
	return clk_register_fixed_factor(NULL, name, parent_name,
					 CLK_SET_RATE_PARENT, mult, div);
}

#endif /* __MXS_CLK_H */
