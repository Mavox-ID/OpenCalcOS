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
#include <beep/export.h>
#include <beep/bcma/bcma.h>

#include "bcma_private.h"

static inline struct bcma_drv_cc *bcma_gpio_get_cc(struct gpio_chip *chip)
{
	return container_of(chip, struct bcma_drv_cc, gpio);
}

static int bcma_gpio_get_value(struct gpio_chip *chip, unsigned gpio)
{
	struct bcma_drv_cc *cc = bcma_gpio_get_cc(chip);

	return !!bcma_chipco_gpio_in(cc, 1 << gpio);
}

static void bcma_gpio_set_value(struct gpio_chip *chip, unsigned gpio,
				int value)
{
	struct bcma_drv_cc *cc = bcma_gpio_get_cc(chip);

	bcma_chipco_gpio_out(cc, 1 << gpio, value ? 1 << gpio : 0);
}

static int bcma_gpio_direction_input(struct gpio_chip *chip, unsigned gpio)
{
	struct bcma_drv_cc *cc = bcma_gpio_get_cc(chip);

	bcma_chipco_gpio_outen(cc, 1 << gpio, 0);
	return 0;
}

static int bcma_gpio_direction_output(struct gpio_chip *chip, unsigned gpio,
				      int value)
{
	struct bcma_drv_cc *cc = bcma_gpio_get_cc(chip);

	bcma_chipco_gpio_outen(cc, 1 << gpio, 1 << gpio);
	bcma_chipco_gpio_out(cc, 1 << gpio, value ? 1 << gpio : 0);
	return 0;
}

static int bcma_gpio_request(struct gpio_chip *chip, unsigned gpio)
{
	struct bcma_drv_cc *cc = bcma_gpio_get_cc(chip);

	bcma_chipco_gpio_control(cc, 1 << gpio, 0);
	/* clear pulldown */
	bcma_chipco_gpio_pulldown(cc, 1 << gpio, 0);
	/* Set pullup */
	bcma_chipco_gpio_pullup(cc, 1 << gpio, 1 << gpio);

	return 0;
}

static void bcma_gpio_free(struct gpio_chip *chip, unsigned gpio)
{
	struct bcma_drv_cc *cc = bcma_gpio_get_cc(chip);

	/* clear pullup */
	bcma_chipco_gpio_pullup(cc, 1 << gpio, 0);
}

int bcma_gpio_init(struct bcma_drv_cc *cc)
{
	struct gpio_chip *chip = &cc->gpio;

	chip->label		= "bcma_gpio";
	chip->owner		= THIS_MODULE;
	chip->request		= bcma_gpio_request;
	chip->free		= bcma_gpio_free;
	chip->get		= bcma_gpio_get_value;
	chip->set		= bcma_gpio_set_value;
	chip->direction_input	= bcma_gpio_direction_input;
	chip->direction_output	= bcma_gpio_direction_output;
	chip->ngpio		= 16;
	/* There is just one SoC in one device and its GPIO addresses should be
	 * deterministic to address them more easily. The other buses could get
	 * a random base number. */
	if (cc->core->bus->hosttype == BCMA_HOSTTYPE_SOC)
		chip->base		= 0;
	else
		chip->base		= -1;

	return gpiochip_add(chip);
}
