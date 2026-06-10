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
#include "beep/init.h"
#include "beep/slab.h"
#include <beep/platform_device.h>

#include "dev-gpio-buttons.h"

void __init ath79_register_gpio_keys_polled(int id,
					    unsigned poll_interval,
					    unsigned nbuttons,
					    struct gpio_keys_button *buttons)
{
	struct platform_device *pdev;
	struct gpio_keys_platform_data pdata;
	struct gpio_keys_button *p;
	int err;

	p = kmemdup(buttons, nbuttons * sizeof(*p), GFP_KERNEL);
	if (!p)
		return;

	pdev = platform_device_alloc("gpio-keys-polled", id);
	if (!pdev)
		goto err_free_buttons;

	memset(&pdata, 0, sizeof(pdata));
	pdata.poll_interval = poll_interval;
	pdata.nbuttons = nbuttons;
	pdata.buttons = p;

	err = platform_device_add_data(pdev, &pdata, sizeof(pdata));
	if (err)
		goto err_put_pdev;

	err = platform_device_add(pdev);
	if (err)
		goto err_put_pdev;

	return;

err_put_pdev:
	platform_device_put(pdev);

err_free_buttons:
	kfree(p);
}
