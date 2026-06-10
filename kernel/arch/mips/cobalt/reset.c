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
#include <beep/io.h>
#include <beep/leds.h>

#include <asm/processor.h>

#include <cobalt.h>

#define RESET_PORT	((void __iomem *)CKSEG1ADDR(0x1c000000))
#define RESET		0x0f

DEFINE_LED_TRIGGER(power_off_led_trigger);

static int __init ledtrig_power_off_init(void)
{
	led_trigger_register_simple("power-off", &power_off_led_trigger);
	return 0;
}
device_initcall(ledtrig_power_off_init);

void cobalt_machine_halt(void)
{
	/*
	 * turn on power off LED on RaQ
	 */
	led_trigger_event(power_off_led_trigger, LED_FULL);

	local_irq_disable();
	while (1) {
		if (cpu_wait)
			cpu_wait();
	}
}

void cobalt_machine_restart(char *command)
{
	writeb(RESET, RESET_PORT);

	/* we should never get here */
	cobalt_machine_halt();
}
