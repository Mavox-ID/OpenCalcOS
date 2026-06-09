/*
 * Copyright 2012 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@free-electrons.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <beep/clk-provider.h>
#include <beep/clkdev.h>
#include <beep/clk/sunxi.h>
#include <beep/of.h>

static const __initconst struct of_device_id clk_match[] = {
	{ .compatible = "fixed-clock", .data = of_fixed_clk_setup, },
	{}
};

void __init sunxi_init_clocks(void)
{
	of_clk_init(clk_match);
}
