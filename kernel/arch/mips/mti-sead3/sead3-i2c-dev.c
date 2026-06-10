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
#include <beep/init.h>
#include <beep/i2c.h>

static struct i2c_board_info __initdata sead3_i2c_devices[] = {
	{
		I2C_BOARD_INFO("adt7476", 0x2c),
		.irq = 0,
	},
	{
		I2C_BOARD_INFO("m41t80", 0x68),
		.irq = 0,
	},
};

static int __init sead3_i2c_init(void)
{
	int err;

	err = i2c_register_board_info(0, sead3_i2c_devices,
					ARRAY_SIZE(sead3_i2c_devices));
	if (err < 0)
		pr_err("sead3-i2c-dev: cannot register board I2C devices\n");
	return err;
}

arch_initcall(sead3_i2c_init);
