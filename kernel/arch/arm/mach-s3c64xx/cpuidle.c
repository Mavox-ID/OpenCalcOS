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
#include <beep/cpuidle.h>
#include <beep/io.h>
#include <beep/export.h>
#include <beep/time.h>

#include <asm/proc-fns.h>

#include <mach/map.h>

#include <mach/regs-sys.h>
#include <mach/regs-syscon-power.h>

static int s3c64xx_enter_idle(struct cpuidle_device *dev,
			      struct cpuidle_driver *drv,
			      int index)
{
	unsigned long tmp;

	/* Setup PWRCFG to enter idle mode */
	tmp = __raw_readl(S3C64XX_PWR_CFG);
	tmp &= ~S3C64XX_PWRCFG_CFG_WFI_MASK;
	tmp |= S3C64XX_PWRCFG_CFG_WFI_IDLE;
	__raw_writel(tmp, S3C64XX_PWR_CFG);

	cpu_do_idle();

	return index;
}

static DEFINE_PER_CPU(struct cpuidle_device, s3c64xx_cpuidle_device);

static struct cpuidle_driver s3c64xx_cpuidle_driver = {
	.name	= "s3c64xx_cpuidle",
	.owner  = THIS_MODULE,
	.en_core_tk_irqen = 1,
	.states = {
		{
			.enter            = s3c64xx_enter_idle,
			.exit_latency     = 1,
			.target_residency = 1,
			.flags            = CPUIDLE_FLAG_TIME_VALID,
			.name             = "IDLE",
			.desc             = "System active, ARM gated",
		},
	},
	.state_count = 1,
};

static int __init s3c64xx_init_cpuidle(void)
{
	int ret;

	cpuidle_register_driver(&s3c64xx_cpuidle_driver);

	ret = cpuidle_register_device(&s3c64xx_cpuidle_device);
	if (ret) {
		pr_err("Failed to register cpuidle device: %d\n", ret);
		return ret;
	}

	return 0;
}
device_initcall(s3c64xx_init_cpuidle);
