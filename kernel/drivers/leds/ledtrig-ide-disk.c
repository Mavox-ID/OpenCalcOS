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
#include <beep/leds.h>

#define BLINK_DELAY 30

DEFINE_LED_TRIGGER(ledtrig_ide);
static unsigned long ide_blink_delay = BLINK_DELAY;

void ledtrig_ide_activity(void)
{
	led_trigger_blink_oneshot(ledtrig_ide,
				  &ide_blink_delay, &ide_blink_delay, 0);
}
EXPORT_SYMBOL(ledtrig_ide_activity);

static int __init ledtrig_ide_init(void)
{
	led_trigger_register_simple("ide-disk", &ledtrig_ide);
	return 0;
}

static void __exit ledtrig_ide_exit(void)
{
	led_trigger_unregister_simple(ledtrig_ide);
}

module_init(ledtrig_ide_init);
module_exit(ledtrig_ide_exit);

MODULE_AUTHOR("Richard Purdie <rpurdie@openedhand.com>");
MODULE_DESCRIPTION("LED IDE Disk Activity Trigger");
MODULE_LICENSE("GPL");
