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
#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/module.h>
#include <beep/interrupt.h>
#include <beep/gpio.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>

#include <mach/regs-gpio.h>
#include <mach/hardware.h>

#include <plat/gpio-core.h>

int s3c2412_gpio_set_sleepcfg(unsigned int pin, unsigned int state)
{
	struct samsung_gpio_chip *chip = samsung_gpiolib_getchip(pin);
	unsigned long offs = pin - chip->chip.base;
	unsigned long flags;
	unsigned long slpcon;

	offs *= 2;

	if (pin < S3C2410_GPB(0))
		return -EINVAL;

	if (pin >= S3C2410_GPF(0) &&
	    pin <= S3C2410_GPG(16))
		return -EINVAL;

	if (pin > S3C2410_GPH(16))
		return -EINVAL;

	local_irq_save(flags);

	slpcon = __raw_readl(chip->base + 0x0C);

	slpcon &= ~(3 << offs);
	slpcon |= state << offs;

	__raw_writel(slpcon, chip->base + 0x0C);

	local_irq_restore(flags);

	return 0;
}

EXPORT_SYMBOL(s3c2412_gpio_set_sleepcfg);
