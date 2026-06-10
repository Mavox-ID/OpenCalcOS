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
#include "common.h"

static int __initdata gpio0_irqs[4] = {
	IRQ_MV78XX0_GPIO_0_7,
	IRQ_MV78XX0_GPIO_8_15,
	IRQ_MV78XX0_GPIO_16_23,
	IRQ_MV78XX0_GPIO_24_31,
};

void __init mv78xx0_init_irq(void)
{
	orion_irq_init(0, IRQ_VIRT_BASE + IRQ_MASK_LOW_OFF);
	orion_irq_init(32, IRQ_VIRT_BASE + IRQ_MASK_HIGH_OFF);
	orion_irq_init(64, IRQ_VIRT_BASE + IRQ_MASK_ERR_OFF);

	/*
	 * Initialize gpiolib for GPIOs 0-31.  (The GPIO interrupt mask
	 * registers for core #1 are at an offset of 0x18 from those of
	 * core #0.)
	 */
	orion_gpio_init(NULL, 0, 32, GPIO_VIRT_BASE,
			mv78xx0_core_index() ? 0x18 : 0,
			IRQ_MV78XX0_GPIO_START, gpio0_irqs);
}
