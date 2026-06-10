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
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/io.h>
#include <beep/suspend.h>
#include <beep/cpuidle.h>
#include <beep/export.h>
#include <asm/suspend.h>
#include <asm/uaccess.h>

static unsigned long cpuidle_mode[] = {
	SUSP_SH_SLEEP, /* regular sleep mode */
	SUSP_SH_SLEEP | SUSP_SH_SF, /* sleep mode + self refresh */
	SUSP_SH_STANDBY | SUSP_SH_SF, /* software standby mode + self refresh */
};

static int cpuidle_sleep_enter(struct cpuidle_device *dev,
				struct cpuidle_driver *drv,
				int index)
{
	unsigned long allowed_mode = SUSP_SH_SLEEP;
	int requested_state = index;
	int allowed_state;
	int k;

	/* convert allowed mode to allowed state */
	for (k = ARRAY_SIZE(cpuidle_mode) - 1; k > 0; k--)
		if (cpuidle_mode[k] == allowed_mode)
			break;

	allowed_state = k;

	/* take the following into account for sleep mode selection:
	 * - allowed_state: best mode allowed by hardware (clock deps)
	 * - requested_state: best mode allowed by software (latencies)
	 */
	k = min_t(int, allowed_state, requested_state);

	sh_mobile_call_standby(cpuidle_mode[k]);

	return k;
}

static struct cpuidle_device cpuidle_dev;
static struct cpuidle_driver cpuidle_driver = {
	.name			= "sh_idle",
	.owner			= THIS_MODULE,
	.en_core_tk_irqen	= 1,
};

void sh_mobile_setup_cpuidle(void)
{
	struct cpuidle_device *dev = &cpuidle_dev;
	struct cpuidle_driver *drv = &cpuidle_driver;
	struct cpuidle_state *state;
	int i;


	for (i = 0; i < CPUIDLE_STATE_MAX; i++) {
		drv->states[i].name[0] = '\0';
		drv->states[i].desc[0] = '\0';
	}

	i = CPUIDLE_DRIVER_STATE_START;

	state = &drv->states[i++];
	snprintf(state->name, CPUIDLE_NAME_LEN, "C1");
	strncpy(state->desc, "SuperH Sleep Mode", CPUIDLE_DESC_LEN);
	state->exit_latency = 1;
	state->target_residency = 1 * 2;
	state->power_usage = 3;
	state->flags = 0;
	state->flags |= CPUIDLE_FLAG_TIME_VALID;
	state->enter = cpuidle_sleep_enter;

	drv->safe_state_index = i-1;

	if (sh_mobile_sleep_supported & SUSP_SH_SF) {
		state = &drv->states[i++];
		snprintf(state->name, CPUIDLE_NAME_LEN, "C2");
		strncpy(state->desc, "SuperH Sleep Mode [SF]",
			CPUIDLE_DESC_LEN);
		state->exit_latency = 100;
		state->target_residency = 1 * 2;
		state->power_usage = 1;
		state->flags = 0;
		state->flags |= CPUIDLE_FLAG_TIME_VALID;
		state->enter = cpuidle_sleep_enter;
	}

	if (sh_mobile_sleep_supported & SUSP_SH_STANDBY) {
		state = &drv->states[i++];
		snprintf(state->name, CPUIDLE_NAME_LEN, "C3");
		strncpy(state->desc, "SuperH Mobile Standby Mode [SF]",
			CPUIDLE_DESC_LEN);
		state->exit_latency = 2300;
		state->target_residency = 1 * 2;
		state->power_usage = 1;
		state->flags = 0;
		state->flags |= CPUIDLE_FLAG_TIME_VALID;
		state->enter = cpuidle_sleep_enter;
	}

	drv->state_count = i;
	dev->state_count = i;

	cpuidle_register_driver(&cpuidle_driver);

	cpuidle_register_device(dev);
}
