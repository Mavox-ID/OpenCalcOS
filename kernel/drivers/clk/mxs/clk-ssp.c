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
#include <beep/clk.h>
#include <beep/module.h>
#include <beep/device.h>
#include <beep/io.h>
#include <beep/spi/mxs-spi.h>

void mxs_ssp_set_clk_rate(struct mxs_ssp *ssp, unsigned int rate)
{
	unsigned int ssp_clk, ssp_sck;
	u32 clock_divide, clock_rate;
	u32 val;

	ssp_clk = clk_get_rate(ssp->clk);

	for (clock_divide = 2; clock_divide <= 254; clock_divide += 2) {
		clock_rate = DIV_ROUND_UP(ssp_clk, rate * clock_divide);
		clock_rate = (clock_rate > 0) ? clock_rate - 1 : 0;
		if (clock_rate <= 255)
			break;
	}

	if (clock_divide > 254) {
		dev_err(ssp->dev,
			"%s: cannot set clock to %d\n", __func__, rate);
		return;
	}

	ssp_sck = ssp_clk / clock_divide / (1 + clock_rate);

	val = readl(ssp->base + HW_SSP_TIMING(ssp));
	val &= ~(BM_SSP_TIMING_CLOCK_DIVIDE | BM_SSP_TIMING_CLOCK_RATE);
	val |= BF_SSP(clock_divide, TIMING_CLOCK_DIVIDE);
	val |= BF_SSP(clock_rate, TIMING_CLOCK_RATE);
	writel(val, ssp->base + HW_SSP_TIMING(ssp));

	ssp->clk_rate = ssp_sck;

	dev_dbg(ssp->dev,
		"%s: clock_divide %d, clock_rate %d, ssp_clk %d, rate_actual %d, rate_requested %d\n",
		__func__, clock_divide, clock_rate, ssp_clk, ssp_sck, rate);
}
EXPORT_SYMBOL_GPL(mxs_ssp_set_clk_rate);
