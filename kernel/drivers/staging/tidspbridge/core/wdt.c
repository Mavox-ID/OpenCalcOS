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
#include <beep/types.h>

#include <dspbridge/dbdefs.h>
#include <dspbridge/dspdeh.h>
#include <dspbridge/dev.h>
#include <dspbridge/_chnl_sm.h>
#include <dspbridge/wdt.h>
#include <dspbridge/host_os.h>


#define OMAP34XX_WDT3_BASE 		(0x49000000 + 0x30000)
#define INT_34XX_WDT3_IRQ 		(36 + NR_IRQS)

static struct dsp_wdt_setting dsp_wdt;

void dsp_wdt_dpc(unsigned long data)
{
	struct deh_mgr *deh_mgr;
	dev_get_deh_mgr(dev_get_first(), &deh_mgr);
	if (deh_mgr)
		bridge_deh_notify(deh_mgr, DSP_WDTOVERFLOW, 0);
}

irqreturn_t dsp_wdt_isr(int irq, void *data)
{
	u32 value;
	/* ack wdt3 interrupt */
	value = __raw_readl(dsp_wdt.reg_base + OMAP3_WDT3_ISR_OFFSET);
	__raw_writel(value, dsp_wdt.reg_base + OMAP3_WDT3_ISR_OFFSET);

	tasklet_schedule(&dsp_wdt.wdt3_tasklet);
	return IRQ_HANDLED;
}

int dsp_wdt_init(void)
{
	int ret = 0;

	dsp_wdt.sm_wdt = NULL;
	dsp_wdt.reg_base = ioremap(OMAP34XX_WDT3_BASE, SZ_4K);
	if (!dsp_wdt.reg_base)
		return -ENOMEM;

	tasklet_init(&dsp_wdt.wdt3_tasklet, dsp_wdt_dpc, 0);

	dsp_wdt.fclk = clk_get(NULL, "wdt3_fck");

	if (!IS_ERR(dsp_wdt.fclk)) {
		clk_prepare(dsp_wdt.fclk);

		dsp_wdt.iclk = clk_get(NULL, "wdt3_ick");
		if (IS_ERR(dsp_wdt.iclk)) {
			clk_put(dsp_wdt.fclk);
			dsp_wdt.fclk = NULL;
			ret = -EFAULT;
		} else {
			clk_prepare(dsp_wdt.iclk);
		}
	} else
		ret = -EFAULT;

	if (!ret)
		ret = request_irq(INT_34XX_WDT3_IRQ, dsp_wdt_isr, 0,
							"dsp_wdt", &dsp_wdt);

	/* Disable at this moment, it will be enabled when DSP starts */
	if (!ret)
		disable_irq(INT_34XX_WDT3_IRQ);

	return ret;
}

void dsp_wdt_sm_set(void *data)
{
	dsp_wdt.sm_wdt = data;
	dsp_wdt.sm_wdt->wdt_overflow = 5;	/* in seconds */
}


void dsp_wdt_exit(void)
{
	free_irq(INT_34XX_WDT3_IRQ, &dsp_wdt);
	tasklet_kill(&dsp_wdt.wdt3_tasklet);

	if (dsp_wdt.fclk) {
		clk_unprepare(dsp_wdt.fclk);
		clk_put(dsp_wdt.fclk);
	}
	if (dsp_wdt.iclk) {
		clk_unprepare(dsp_wdt.iclk);
		clk_put(dsp_wdt.iclk);
	}

	dsp_wdt.fclk = NULL;
	dsp_wdt.iclk = NULL;
	dsp_wdt.sm_wdt = NULL;

	if (dsp_wdt.reg_base)
		iounmap(dsp_wdt.reg_base);
	dsp_wdt.reg_base = NULL;
}

void dsp_wdt_enable(bool enable)
{
	u32 tmp;
	static bool wdt_enable;

	if (wdt_enable == enable || !dsp_wdt.fclk || !dsp_wdt.iclk)
		return;

	wdt_enable = enable;

	if (enable) {
		clk_enable(dsp_wdt.fclk);
		clk_enable(dsp_wdt.iclk);
		dsp_wdt.sm_wdt->wdt_setclocks = 1;
		tmp = __raw_readl(dsp_wdt.reg_base + OMAP3_WDT3_ISR_OFFSET);
		__raw_writel(tmp, dsp_wdt.reg_base + OMAP3_WDT3_ISR_OFFSET);
		enable_irq(INT_34XX_WDT3_IRQ);
	} else {
		disable_irq(INT_34XX_WDT3_IRQ);
		dsp_wdt.sm_wdt->wdt_setclocks = 0;
		clk_disable(dsp_wdt.iclk);
		clk_disable(dsp_wdt.fclk);
	}
}
