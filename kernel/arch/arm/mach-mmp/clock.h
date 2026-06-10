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
#include <beep/clkdev.h>

struct clkops {
	void			(*enable)(struct clk *);
	void			(*disable)(struct clk *);
	unsigned long		(*getrate)(struct clk *);
	int			(*setrate)(struct clk *, unsigned long);
};

struct clk {
	const struct clkops	*ops;

	void __iomem	*clk_rst;	/* clock reset control register */
	int		fnclksel;	/* functional clock select (APBC) */
	uint32_t	enable_val;	/* value for clock enable (APMU) */
	unsigned long	rate;
	int		enabled;
};

extern struct clkops apbc_clk_ops;
extern struct clkops apmu_clk_ops;

#define APBC_CLK(_name, _reg, _fnclksel, _rate)			\
struct clk clk_##_name = {					\
		.clk_rst	= APBC_##_reg,			\
		.fnclksel	= _fnclksel,			\
		.rate		= _rate,			\
		.ops		= &apbc_clk_ops,		\
}

#define APBC_CLK_OPS(_name, _reg, _fnclksel, _rate, _ops)	\
struct clk clk_##_name = {					\
		.clk_rst	= APBC_##_reg,			\
		.fnclksel	= _fnclksel,			\
		.rate		= _rate,			\
		.ops		= _ops,				\
}

#define APMU_CLK(_name, _reg, _eval, _rate)			\
struct clk clk_##_name = {					\
		.clk_rst	= APMU_##_reg,			\
		.enable_val	= _eval,			\
		.rate		= _rate,			\
		.ops		= &apmu_clk_ops,		\
}

#define APMU_CLK_OPS(_name, _reg, _eval, _rate, _ops)		\
struct clk clk_##_name = {					\
		.clk_rst	= APMU_##_reg,			\
		.enable_val	= _eval,			\
		.rate		= _rate,			\
		.ops		= _ops,				\
}

#define INIT_CLKREG(_clk, _devname, _conname)			\
	{							\
		.clk		= _clk,				\
		.dev_id		= _devname,			\
		.con_id		= _conname,			\
	}

extern struct clk clk_pxa168_gpio;
extern struct clk clk_pxa168_timers;
