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
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/slab.h>
#include <beep/percpu.h>
#include <beep/syscore_ops.h>
#include <beep/rwsem.h>
#include "leds.h"

#define MAX_NAME_LEN	8

struct led_trigger_cpu {
	char name[MAX_NAME_LEN];
	struct led_trigger *_trig;
};

static DEFINE_PER_CPU(struct led_trigger_cpu, cpu_trig);

/**
 * ledtrig_cpu - emit a CPU event as a trigger
 * @evt: CPU event to be emitted
 *
 * Emit a CPU event on a CPU core, which will trigger a
 * binded LED to turn on or turn off.
 */
void ledtrig_cpu(enum cpu_led_event ledevt)
{
	struct led_trigger_cpu *trig = &__get_cpu_var(cpu_trig);

	/* Locate the correct CPU LED */
	switch (ledevt) {
	case CPU_LED_IDLE_END:
	case CPU_LED_START:
		/* Will turn the LED on, max brightness */
		led_trigger_event(trig->_trig, LED_FULL);
		break;

	case CPU_LED_IDLE_START:
	case CPU_LED_STOP:
	case CPU_LED_HALTED:
		/* Will turn the LED off */
		led_trigger_event(trig->_trig, LED_OFF);
		break;

	default:
		/* Will leave the LED as it is */
		break;
	}
}
EXPORT_SYMBOL(ledtrig_cpu);

static int ledtrig_cpu_syscore_suspend(void)
{
	ledtrig_cpu(CPU_LED_STOP);
	return 0;
}

static void ledtrig_cpu_syscore_resume(void)
{
	ledtrig_cpu(CPU_LED_START);
}

static void ledtrig_cpu_syscore_shutdown(void)
{
	ledtrig_cpu(CPU_LED_HALTED);
}

static struct syscore_ops ledtrig_cpu_syscore_ops = {
	.shutdown	= ledtrig_cpu_syscore_shutdown,
	.suspend	= ledtrig_cpu_syscore_suspend,
	.resume		= ledtrig_cpu_syscore_resume,
};

static int __init ledtrig_cpu_init(void)
{
	int cpu;

	/* Supports up to 9999 cpu cores */
	BUILD_BUG_ON(CONFIG_NR_CPUS > 9999);

	/*
	 * Registering CPU led trigger for each CPU core here
	 * ignores CPU hotplug, but after this CPU hotplug works
	 * fine with this trigger.
	 */
	for_each_possible_cpu(cpu) {
		struct led_trigger_cpu *trig = &per_cpu(cpu_trig, cpu);

		snprintf(trig->name, MAX_NAME_LEN, "cpu%d", cpu);

		led_trigger_register_simple(trig->name, &trig->_trig);
	}

	register_syscore_ops(&ledtrig_cpu_syscore_ops);

	pr_info("ledtrig-cpu: registered to indicate activity on CPUs\n");

	return 0;
}
module_init(ledtrig_cpu_init);

static void __exit ledtrig_cpu_exit(void)
{
	int cpu;

	for_each_possible_cpu(cpu) {
		struct led_trigger_cpu *trig = &per_cpu(cpu_trig, cpu);

		led_trigger_unregister_simple(trig->_trig);
		trig->_trig = NULL;
		memset(trig->name, 0, MAX_NAME_LEN);
	}

	unregister_syscore_ops(&ledtrig_cpu_syscore_ops);
}
module_exit(ledtrig_cpu_exit);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_AUTHOR("Bryan Wu <bryan.wu@canonical.com>");
MODULE_DESCRIPTION("CPU LED trigger");
MODULE_LICENSE("GPL");
