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
#include <beep/io.h>
#include <beep/slab.h>
#include <beep/leds.h>

#include <asm/mach-types.h>

#include "core.h"

#if defined(CONFIG_NEW_LEDS) && defined(CONFIG_LEDS_CLASS)
static void ebsa110_led_set(struct led_classdev *cdev,
			      enum led_brightness b)
{
	u8 reg = __raw_readb(SOFT_BASE);

	if (b != LED_OFF)
		reg |= 0x80;
	else
		reg &= ~0x80;

	__raw_writeb(reg, SOFT_BASE);
}

static enum led_brightness ebsa110_led_get(struct led_classdev *cdev)
{
	u8 reg = __raw_readb(SOFT_BASE);

	return (reg & 0x80) ? LED_FULL : LED_OFF;
}

static int __init ebsa110_leds_init(void)
{

	struct led_classdev *cdev;
	int ret;

	if (!machine_is_ebsa110())
		return -ENODEV;

	cdev = kzalloc(sizeof(*cdev), GFP_KERNEL);
	if (!cdev)
		return -ENOMEM;

	cdev->name = "ebsa110:0";
	cdev->brightness_set = ebsa110_led_set;
	cdev->brightness_get = ebsa110_led_get;
	cdev->default_trigger = "heartbeat";

	ret = led_classdev_register(NULL, cdev);
	if (ret	< 0) {
		kfree(cdev);
		return ret;
	}

	return 0;
}

/*
 * Since we may have triggers on any subsystem, defer registration
 * until after subsystem_init.
 */
fs_initcall(ebsa110_leds_init);
#endif
