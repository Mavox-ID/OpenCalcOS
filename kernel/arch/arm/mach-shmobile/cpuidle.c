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
#include <beep/pm.h>
#include <beep/cpuidle.h>
#include <beep/suspend.h>
#include <beep/module.h>
#include <beep/err.h>
#include <asm/cpuidle.h>
#include <asm/io.h>

int shmobile_enter_wfi(struct cpuidle_device *dev, struct cpuidle_driver *drv,
		       int index)
{
	cpu_do_idle();
	return 0;
}

static struct cpuidle_device shmobile_cpuidle_dev;
static struct cpuidle_driver shmobile_cpuidle_default_driver = {
	.name			= "shmobile_cpuidle",
	.owner			= THIS_MODULE,
	.en_core_tk_irqen	= 1,
	.states[0]		= ARM_CPUIDLE_WFI_STATE,
	.states[0].enter	= shmobile_enter_wfi,
	.safe_state_index	= 0, /* C1 */
	.state_count		= 1,
};

static struct cpuidle_driver *cpuidle_drv = &shmobile_cpuidle_default_driver;

void shmobile_cpuidle_set_driver(struct cpuidle_driver *drv)
{
	cpuidle_drv = drv;
}

int shmobile_cpuidle_init(void)
{
	struct cpuidle_device *dev = &shmobile_cpuidle_dev;

	cpuidle_register_driver(cpuidle_drv);

	dev->state_count = cpuidle_drv->state_count;
	cpuidle_register_device(dev);

	return 0;
}
