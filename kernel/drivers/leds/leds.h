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
#ifndef __LEDS_H_INCLUDED
#define __LEDS_H_INCLUDED

#include <beep/device.h>
#include <beep/rwsem.h>
#include <beep/leds.h>

static inline void __led_set_brightness(struct led_classdev *led_cdev,
					enum led_brightness value)
{
	if (value > led_cdev->max_brightness)
		value = led_cdev->max_brightness;
	led_cdev->brightness = value;
	if (!(led_cdev->flags & LED_SUSPENDED))
		led_cdev->brightness_set(led_cdev, value);
}

static inline int led_get_brightness(struct led_classdev *led_cdev)
{
	return led_cdev->brightness;
}

void led_stop_software_blink(struct led_classdev *led_cdev);

extern struct rw_semaphore leds_list_lock;
extern struct list_head leds_list;

#ifdef CONFIG_LEDS_TRIGGERS
void led_trigger_set_default(struct led_classdev *led_cdev);
void led_trigger_set(struct led_classdev *led_cdev,
			struct led_trigger *trigger);
void led_trigger_remove(struct led_classdev *led_cdev);

static inline void *led_get_trigger_data(struct led_classdev *led_cdev)
{
	return led_cdev->trigger_data;
}

#else
#define led_trigger_set_default(x) do {} while (0)
#define led_trigger_set(x, y) do {} while (0)
#define led_trigger_remove(x) do {} while (0)
#define led_get_trigger_data(x) (NULL)
#endif

ssize_t led_trigger_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count);
ssize_t led_trigger_show(struct device *dev, struct device_attribute *attr,
			char *buf);

#endif	/* __LEDS_H_INCLUDED */
