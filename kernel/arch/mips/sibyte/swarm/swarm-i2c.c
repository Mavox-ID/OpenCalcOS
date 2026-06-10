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
#include <beep/init.h>
#include <beep/kernel.h>


static struct i2c_board_info swarm_i2c_info1[] __initdata = {
	{
		I2C_BOARD_INFO("m41t81", 0x68),
	},
};

static int __init swarm_i2c_init(void)
{
	int err;

	err = i2c_register_board_info(1, swarm_i2c_info1,
				      ARRAY_SIZE(swarm_i2c_info1));
	if (err < 0)
		printk(KERN_ERR
		       "swarm-i2c: cannot register board I2C devices\n");
	return err;
}

arch_initcall(swarm_i2c_init);
