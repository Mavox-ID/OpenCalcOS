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

#include <mach/hardware.h>
#include <mach/platform.h>

#ifdef VERSATILE_SYS_BASE
#define LEDREG	(__io_address(VERSATILE_SYS_BASE) + VERSATILE_SYS_LED_OFFSET)
#endif

#ifdef REALVIEW_SYS_BASE
#define LEDREG	(__io_address(REALVIEW_SYS_BASE) + REALVIEW_SYS_LED_OFFSET)
#endif

struct versatile_led {
	struct led_classdev	cdev;
	u8			mask;
};

/*
 * The triggers lines up below will only be used if the
 * LED triggers are compiled in.
 */
static const struct {
	const char *name;
	const char *trigger;
} versatile_leds[] = {
	{ "versatile:0", "heartbeat", },
	{ "versatile:1", "mmc0", },
	{ "versatile:2", "cpu0" },
	{ "versatile:3", "cpu1" },
	{ "versatile:4", "cpu2" },
	{ "versatile:5", "cpu3" },
	{ "versatile:6", },
	{ "versatile:7", },
};

static void versatile_led_set(struct led_classdev *cdev,
			      enum led_brightness b)
{
	struct versatile_led *led = container_of(cdev,
						 struct versatile_led, cdev);
	u32 reg = readl(LEDREG);

	if (b != LED_OFF)
		reg |= led->mask;
	else
		reg &= ~led->mask;
	writel(reg, LEDREG);
}

static enum led_brightness versatile_led_get(struct led_classdev *cdev)
{
	struct versatile_led *led = container_of(cdev,
						 struct versatile_led, cdev);
	u32 reg = readl(LEDREG);

	return (reg & led->mask) ? LED_FULL : LED_OFF;
}

static int __init versatile_leds_init(void)
{
	int i;

	/* All ON */
	writel(0xff, LEDREG);
	for (i = 0; i < ARRAY_SIZE(versatile_leds); i++) {
		struct versatile_led *led;

		led = kzalloc(sizeof(*led), GFP_KERNEL);
		if (!led)
			break;

		led->cdev.name = versatile_leds[i].name;
		led->cdev.brightness_set = versatile_led_set;
		led->cdev.brightness_get = versatile_led_get;
		led->cdev.default_trigger = versatile_leds[i].trigger;
		led->mask = BIT(i);

		if (led_classdev_register(NULL, &led->cdev) < 0) {
			kfree(led);
			break;
		}
	}

	return 0;
}

/*
 * Since we may have triggers on any subsystem, defer registration
 * until after subsystem_init.
 */
fs_initcall(versatile_leds_init);
