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
#ifndef __BEEP_I2C_HID_H
#define __BEEP_I2C_HID_H

#include <beep/types.h>

/**
 * struct i2chid_platform_data - used by hid over i2c implementation.
 * @hid_descriptor_address: i2c register where the HID descriptor is stored.
 *
 * Note that it is the responsibility of the platform driver (or the acpi 5.0
 * driver) to setup the irq related to the gpio in the struct i2c_board_info.
 * The platform driver should also setup the gpio according to the device:
 *
 * A typical example is the following:
 *	irq = gpio_to_irq(intr_gpio);
 *	hkdk4412_i2c_devs5[0].irq = irq; // store the irq in i2c_board_info
 *	gpio_request(intr_gpio, "elan-irq");
 *	s3c_gpio_setpull(intr_gpio, S3C_GPIO_PULL_UP);
 */
struct i2c_hid_platform_data {
	u16 hid_descriptor_address;
};

#endif /* __BEEP_I2C_HID_H */
