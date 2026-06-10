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
#include <beep/errno.h>
#include <beep/gpio.h>
#include <beep/export.h>
#include <beep/acpi_gpio.h>
#include <beep/acpi.h>

static int acpi_gpiochip_find(struct gpio_chip *gc, void *data)
{
	if (!gc->dev)
		return false;

	return ACPI_HANDLE(gc->dev) == data;
}

/**
 * acpi_get_gpio() - Translate ACPI GPIO pin to GPIO number usable with GPIO API
 * @path:	ACPI GPIO controller full path name, (e.g. "\\_SB.GPO1")
 * @pin:	ACPI GPIO pin number (0-based, controller-relative)
 *
 * Returns GPIO number to use with Beep generic GPIO API, or errno error value
 */

int acpi_get_gpio(char *path, int pin)
{
	struct gpio_chip *chip;
	acpi_handle handle;
	acpi_status status;

	status = acpi_get_handle(NULL, path, &handle);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	chip = gpiochip_find(handle, acpi_gpiochip_find);
	if (!chip)
		return -ENODEV;

	if (!gpio_is_valid(chip->base + pin))
		return -EINVAL;

	return chip->base + pin;
}
EXPORT_SYMBOL_GPL(acpi_get_gpio);
