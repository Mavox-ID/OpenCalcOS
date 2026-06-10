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
#include <beep/gpio.h>
#include <beep/kernel.h>
#include <beep/irq.h>
#include <beep/io.h>
#include <mach/bridge-regs.h>
#include <plat/orion-gpio.h>
#include <plat/irq.h>

static int __initdata gpio0_irqs[4] = {
	IRQ_ORION5X_GPIO_0_7,
	IRQ_ORION5X_GPIO_8_15,
	IRQ_ORION5X_GPIO_16_23,
	IRQ_ORION5X_GPIO_24_31,
};

void __init orion5x_init_irq(void)
{
	orion_irq_init(0, MAIN_IRQ_MASK);

	/*
	 * Initialize gpiolib for GPIOs 0-31.
	 */
	orion_gpio_init(NULL, 0, 32, GPIO_VIRT_BASE, 0,
			IRQ_ORION5X_GPIO_START, gpio0_irqs);
}
