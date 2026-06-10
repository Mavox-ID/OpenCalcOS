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
#include <beep/ioport.h>
#include <beep/slab.h>
#include <beep/leds.h>

#include <asm/mach-types.h>

#if defined(CONFIG_NEW_LEDS) && defined(CONFIG_LEDS_CLASS)
struct shark_led {
	struct led_classdev cdev;
	u8 mask;
};

/*
 * The triggers lines up below will only be used if the
 * LED triggers are compiled in.
 */
static const struct {
	const char *name;
	const char *trigger;
} shark_leds[] = {
	{ "shark:amber0", "default-on", },	/* Bit 5 */
	{ "shark:green", "heartbeat", },	/* Bit 6 */
	{ "shark:amber1", "cpu0" },		/* Bit 7 */
};

static u16 led_reg_read(void)
{
	outw(0x09, 0x24);
	return inw(0x26);
}

static void led_reg_write(u16 value)
{
	outw(0x09, 0x24);
	outw(value, 0x26);
}

static void shark_led_set(struct led_classdev *cdev,
			      enum led_brightness b)
{
	struct shark_led *led = container_of(cdev,
						 struct shark_led, cdev);
	u16 reg = led_reg_read();

	if (b != LED_OFF)
		reg |= led->mask;
	else
		reg &= ~led->mask;

	led_reg_write(reg);
}

static enum led_brightness shark_led_get(struct led_classdev *cdev)
{
	struct shark_led *led = container_of(cdev,
						 struct shark_led, cdev);
	u16 reg = led_reg_read();

	return (reg & led->mask) ? LED_FULL : LED_OFF;
}

static int __init shark_leds_init(void)
{
	int i;
	u16 reg;

	if (!machine_is_shark())
		return -ENODEV;

	for (i = 0; i < ARRAY_SIZE(shark_leds); i++) {
		struct shark_led *led;

		led = kzalloc(sizeof(*led), GFP_KERNEL);
		if (!led)
			break;

		led->cdev.name = shark_leds[i].name;
		led->cdev.brightness_set = shark_led_set;
		led->cdev.brightness_get = shark_led_get;
		led->cdev.default_trigger = shark_leds[i].trigger;

		/* Count in 5 bits offset */
		led->mask = BIT(i + 5);

		if (led_classdev_register(NULL, &led->cdev) < 0) {
			kfree(led);
			break;
		}
	}

	/* Make LEDs independent of power-state */
	request_region(0x24, 4, "led_reg");
	reg = led_reg_read();
	reg |= 1 << 10;
	led_reg_write(reg);

	return 0;
}

/*
 * Since we may have triggers on any subsystem, defer registration
 * until after subsystem_init.
 */
fs_initcall(shark_leds_init);
#endif
