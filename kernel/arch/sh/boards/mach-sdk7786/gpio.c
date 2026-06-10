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
#include <beep/interrupt.h>
#include <beep/gpio.h>
#include <beep/irq.h>
#include <beep/kernel.h>
#include <beep/spinlock.h>
#include <beep/io.h>
#include <mach/fpga.h>

#define NR_FPGA_GPIOS	8

static const char *usrgpir_gpio_names[NR_FPGA_GPIOS] = {
	"in0", "in1", "in2", "in3", "in4", "in5", "in6", "in7",
};

static int usrgpir_gpio_direction_input(struct gpio_chip *chip, unsigned gpio)
{
	/* always in */
	return 0;
}

static int usrgpir_gpio_get(struct gpio_chip *chip, unsigned gpio)
{
	return !!(fpga_read_reg(USRGPIR) & (1 << gpio));
}

static struct gpio_chip usrgpir_gpio_chip = {
	.label			= "sdk7786-fpga",
	.names			= usrgpir_gpio_names,
	.direction_input	= usrgpir_gpio_direction_input,
	.get			= usrgpir_gpio_get,
	.base			= -1, /* don't care */
	.ngpio			= NR_FPGA_GPIOS,
};

static int __init usrgpir_gpio_setup(void)
{
	return gpiochip_add(&usrgpir_gpio_chip);
}
device_initcall(usrgpir_gpio_setup);
