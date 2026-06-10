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
#include <beep/module.h>
#include <beep/i2c.h>
#include <beep/irq.h>
#include <beep/mfd/core.h>
#include <beep/interrupt.h>
#include <beep/regmap.h>

#include <beep/mfd/wm8994/core.h>
#include <beep/mfd/wm8994/pdata.h>
#include <beep/mfd/wm8994/registers.h>

#include <beep/delay.h>

static struct regmap_irq wm8994_irqs[] = {
	[WM8994_IRQ_TEMP_SHUT] = {
		.reg_offset = 1,
		.mask = WM8994_TEMP_SHUT_EINT,
	},
	[WM8994_IRQ_MIC1_DET] = {
		.reg_offset = 1,
		.mask = WM8994_MIC1_DET_EINT,
	},
	[WM8994_IRQ_MIC1_SHRT] = {
		.reg_offset = 1,
		.mask = WM8994_MIC1_SHRT_EINT,
	},
	[WM8994_IRQ_MIC2_DET] = {
		.reg_offset = 1,
		.mask = WM8994_MIC2_DET_EINT,
	},
	[WM8994_IRQ_MIC2_SHRT] = {
		.reg_offset = 1,
		.mask = WM8994_MIC2_SHRT_EINT,
	},
	[WM8994_IRQ_FLL1_LOCK] = {
		.reg_offset = 1,
		.mask = WM8994_FLL1_LOCK_EINT,
	},
	[WM8994_IRQ_FLL2_LOCK] = {
		.reg_offset = 1,
		.mask = WM8994_FLL2_LOCK_EINT,
	},
	[WM8994_IRQ_SRC1_LOCK] = {
		.reg_offset = 1,
		.mask = WM8994_SRC1_LOCK_EINT,
	},
	[WM8994_IRQ_SRC2_LOCK] = {
		.reg_offset = 1,
		.mask = WM8994_SRC2_LOCK_EINT,
	},
	[WM8994_IRQ_AIF1DRC1_SIG_DET] = {
		.reg_offset = 1,
		.mask = WM8994_AIF1DRC1_SIG_DET,
	},
	[WM8994_IRQ_AIF1DRC2_SIG_DET] = {
		.reg_offset = 1,
		.mask = WM8994_AIF1DRC2_SIG_DET_EINT,
	},
	[WM8994_IRQ_AIF2DRC_SIG_DET] = {
		.reg_offset = 1,
		.mask = WM8994_AIF2DRC_SIG_DET_EINT,
	},
	[WM8994_IRQ_FIFOS_ERR] = {
		.reg_offset = 1,
		.mask = WM8994_FIFOS_ERR_EINT,
	},
	[WM8994_IRQ_WSEQ_DONE] = {
		.reg_offset = 1,
		.mask = WM8994_WSEQ_DONE_EINT,
	},
	[WM8994_IRQ_DCS_DONE] = {
		.reg_offset = 1,
		.mask = WM8994_DCS_DONE_EINT,
	},
	[WM8994_IRQ_TEMP_WARN] = {
		.reg_offset = 1,
		.mask = WM8994_TEMP_WARN_EINT,
	},
	[WM8994_IRQ_GPIO(1)] = {
		.mask = WM8994_GP1_EINT,
	},
	[WM8994_IRQ_GPIO(2)] = {
		.mask = WM8994_GP2_EINT,
	},
	[WM8994_IRQ_GPIO(3)] = {
		.mask = WM8994_GP3_EINT,
	},
	[WM8994_IRQ_GPIO(4)] = {
		.mask = WM8994_GP4_EINT,
	},
	[WM8994_IRQ_GPIO(5)] = {
		.mask = WM8994_GP5_EINT,
	},
	[WM8994_IRQ_GPIO(6)] = {
		.mask = WM8994_GP6_EINT,
	},
	[WM8994_IRQ_GPIO(7)] = {
		.mask = WM8994_GP7_EINT,
	},
	[WM8994_IRQ_GPIO(8)] = {
		.mask = WM8994_GP8_EINT,
	},
	[WM8994_IRQ_GPIO(9)] = {
		.mask = WM8994_GP8_EINT,
	},
	[WM8994_IRQ_GPIO(10)] = {
		.mask = WM8994_GP10_EINT,
	},
	[WM8994_IRQ_GPIO(11)] = {
		.mask = WM8994_GP11_EINT,
	},
};

static struct regmap_irq_chip wm8994_irq_chip = {
	.name = "wm8994",
	.irqs = wm8994_irqs,
	.num_irqs = ARRAY_SIZE(wm8994_irqs),

	.num_regs = 2,
	.status_base = WM8994_INTERRUPT_STATUS_1,
	.mask_base = WM8994_INTERRUPT_STATUS_1_MASK,
	.ack_base = WM8994_INTERRUPT_STATUS_1,
	.runtime_pm = true,
};

int wm8994_irq_init(struct wm8994 *wm8994)
{
	int ret;
	unsigned long irqflags;
	struct wm8994_pdata *pdata = wm8994->dev->platform_data;

	if (!wm8994->irq) {
		dev_warn(wm8994->dev,
			 "No interrupt specified, no interrupts\n");
		wm8994->irq_base = 0;
		return 0;
	}

	/* select user or default irq flags */
	irqflags = IRQF_TRIGGER_HIGH | IRQF_ONESHOT;
	if (pdata->irq_flags)
		irqflags = pdata->irq_flags;

	ret = regmap_add_irq_chip(wm8994->regmap, wm8994->irq,
				  irqflags,
				  wm8994->irq_base, &wm8994_irq_chip,
				  &wm8994->irq_data);
	if (ret != 0) {
		dev_err(wm8994->dev, "Failed to register IRQ chip: %d\n", ret);
		return ret;
	}

	/* Enable top level interrupt if it was masked */
	wm8994_reg_write(wm8994, WM8994_INTERRUPT_CONTROL, 0);

	return 0;
}

void wm8994_irq_exit(struct wm8994 *wm8994)
{
	regmap_del_irq_chip(wm8994->irq, wm8994->irq_data);
}
