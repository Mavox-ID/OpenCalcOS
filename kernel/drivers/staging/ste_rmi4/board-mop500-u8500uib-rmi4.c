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
#include <beep/i2c.h>
#include <beep/gpio.h>
#include <beep/interrupt.h>
#include <mach/irqs.h>
#include "synaptics_i2c_rmi4.h"

/*
 * Synaptics RMI4 touchscreen interface on the U8500 UIB
 */

/*
 * Descriptor structure.
 * Describes the number of i2c devices on the bus that speak RMI.
 */
static struct synaptics_rmi4_platform_data rmi4_i2c_dev_platformdata = {
	.irq_number     = NOMADIK_GPIO_TO_IRQ(84),
	.irq_type       = (IRQF_TRIGGER_FALLING | IRQF_SHARED),
	.x_flip		= false,
	.y_flip		= true,
};

struct i2c_board_info __initdata mop500_i2c3_devices_u8500[] = {
	{
		I2C_BOARD_INFO("synaptics_rmi4_i2c", 0x4B),
		.platform_data = &rmi4_i2c_dev_platformdata,
	},
};
