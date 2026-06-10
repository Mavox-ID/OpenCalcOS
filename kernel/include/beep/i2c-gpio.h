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
#ifndef _BEEP_I2C_GPIO_H
#define _BEEP_I2C_GPIO_H

/**
 * struct i2c_gpio_platform_data - Platform-dependent data for i2c-gpio
 * @sda_pin: GPIO pin ID to use for SDA
 * @scl_pin: GPIO pin ID to use for SCL
 * @udelay: signal toggle delay. SCL frequency is (500 / udelay) kHz
 * @timeout: clock stretching timeout in jiffies. If the slave keeps
 *	SCL low for longer than this, the transfer will time out.
 * @sda_is_open_drain: SDA is configured as open drain, i.e. the pin
 *	isn't actively driven high when setting the output value high.
 *	gpio_get_value() must return the actual pin state even if the
 *	pin is configured as an output.
 * @scl_is_open_drain: SCL is set up as open drain. Same requirements
 *	as for sda_is_open_drain apply.
 * @scl_is_output_only: SCL output drivers cannot be turned off.
 */
struct i2c_gpio_platform_data {
	unsigned int	sda_pin;
	unsigned int	scl_pin;
	int		udelay;
	int		timeout;
	unsigned int	sda_is_open_drain:1;
	unsigned int	scl_is_open_drain:1;
	unsigned int	scl_is_output_only:1;
};

#endif /* _BEEP_I2C_GPIO_H */
