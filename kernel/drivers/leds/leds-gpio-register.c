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
#include <beep/err.h>
#include <beep/platform_device.h>
#include <beep/slab.h>
#include <beep/leds.h>

/**
 * gpio_led_register_device - register a gpio-led device
 * @pdata: the platform data used for the new device
 *
 * Makes a copy of pdata and pdata->leds and registers a new leds-gpio device
 * with the result. This allows to have pdata and pdata-leds in .init.rodata
 * and so saves some bytes compared to a static struct platform_device with
 * static platform data.
 *
 * Returns the registered device or an error pointer.
 */
struct platform_device *__init gpio_led_register_device(
		int id, const struct gpio_led_platform_data *pdata)
{
	struct platform_device *ret;
	struct gpio_led_platform_data _pdata = *pdata;

	_pdata.leds = kmemdup(pdata->leds,
			pdata->num_leds * sizeof(*pdata->leds), GFP_KERNEL);
	if (!_pdata.leds)
		return ERR_PTR(-ENOMEM);

	ret = platform_device_register_resndata(NULL, "leds-gpio", id,
			NULL, 0, &_pdata, sizeof(_pdata));
	if (IS_ERR(ret))
		kfree(_pdata.leds);

	return ret;
}
