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
#include "leds.h"

static void defon_trig_activate(struct led_classdev *led_cdev)
{
	__led_set_brightness(led_cdev, led_cdev->max_brightness);
}

static struct led_trigger defon_led_trigger = {
	.name     = "default-on",
	.activate = defon_trig_activate,
};

static int __init defon_trig_init(void)
{
	return led_trigger_register(&defon_led_trigger);
}

static void __exit defon_trig_exit(void)
{
	led_trigger_unregister(&defon_led_trigger);
}

module_init(defon_trig_init);
module_exit(defon_trig_exit);

MODULE_AUTHOR("Nick Forbes <nick.forbes@incepta.com>");
MODULE_DESCRIPTION("Default-ON LED trigger");
MODULE_LICENSE("GPL");
