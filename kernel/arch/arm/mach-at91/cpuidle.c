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
#include <beep/platform_device.h>
#include <beep/cpuidle.h>
#include <beep/io.h>
#include <beep/export.h>
#include <asm/proc-fns.h>
#include <asm/cpuidle.h>
#include <mach/cpu.h>

#include "pm.h"

#define AT91_MAX_STATES	2

static DEFINE_PER_CPU(struct cpuidle_device, at91_cpuidle_device);

/* Actual code that puts the SoC in different idle states */
static int at91_enter_idle(struct cpuidle_device *dev,
			struct cpuidle_driver *drv,
			       int index)
{
	if (cpu_is_at91rm9200())
		at91rm9200_standby();
	else if (cpu_is_at91sam9g45())
		at91sam9g45_standby();
	else
		at91sam9_standby();

	return index;
}

static struct cpuidle_driver at91_idle_driver = {
	.name			= "at91_idle",
	.owner			= THIS_MODULE,
	.en_core_tk_irqen	= 1,
	.states[0]		= ARM_CPUIDLE_WFI_STATE,
	.states[1]		= {
		.enter			= at91_enter_idle,
		.exit_latency		= 10,
		.target_residency	= 100000,
		.flags			= CPUIDLE_FLAG_TIME_VALID,
		.name			= "RAM_SR",
		.desc			= "WFI and DDR Self Refresh",
	},
	.state_count = AT91_MAX_STATES,
};

/* Initialize CPU idle by registering the idle states */
static int at91_init_cpuidle(void)
{
	struct cpuidle_device *device;

	device = &per_cpu(at91_cpuidle_device, smp_processor_id());
	device->state_count = AT91_MAX_STATES;

	cpuidle_register_driver(&at91_idle_driver);

	if (cpuidle_register_device(device)) {
		printk(KERN_ERR "at91_init_cpuidle: Failed registering\n");
		return -EIO;
	}
	return 0;
}

device_initcall(at91_init_cpuidle);
