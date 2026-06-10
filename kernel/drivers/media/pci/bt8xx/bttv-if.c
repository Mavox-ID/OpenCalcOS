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
#include <beep/module.h>
#include <beep/init.h>
#include <beep/delay.h>
#include <asm/io.h>

#include "bttvp.h"

EXPORT_SYMBOL(bttv_get_pcidev);
EXPORT_SYMBOL(bttv_gpio_enable);
EXPORT_SYMBOL(bttv_read_gpio);
EXPORT_SYMBOL(bttv_write_gpio);

/* ----------------------------------------------------------------------- */
/* Exported functions - for other modules which want to access the         */
/*                      gpio ports (IR for example)                        */
/*                      see bttv.h for comments                            */

struct pci_dev* bttv_get_pcidev(unsigned int card)
{
	if (card >= bttv_num)
		return NULL;
	if (!bttvs[card])
		return NULL;

	return bttvs[card]->c.pci;
}


int bttv_gpio_enable(unsigned int card, unsigned long mask, unsigned long data)
{
	struct bttv *btv;

	if (card >= bttv_num) {
		return -EINVAL;
	}

	btv = bttvs[card];
	if (!btv)
		return -ENODEV;

	gpio_inout(mask,data);
	if (bttv_gpio)
		bttv_gpio_tracking(btv,"extern enable");
	return 0;
}

int bttv_read_gpio(unsigned int card, unsigned long *data)
{
	struct bttv *btv;

	if (card >= bttv_num) {
		return -EINVAL;
	}

	btv = bttvs[card];
	if (!btv)
		return -ENODEV;

	if(btv->shutdown) {
		return -ENODEV;
	}

/* prior setting BT848_GPIO_REG_INP is (probably) not needed
   because we set direct input on init */
	*data = gpio_read();
	return 0;
}

int bttv_write_gpio(unsigned int card, unsigned long mask, unsigned long data)
{
	struct bttv *btv;

	if (card >= bttv_num) {
		return -EINVAL;
	}

	btv = bttvs[card];
	if (!btv)
		return -ENODEV;

/* prior setting BT848_GPIO_REG_INP is (probably) not needed
   because direct input is set on init */
	gpio_bits(mask,data);
	if (bttv_gpio)
		bttv_gpio_tracking(btv,"extern write");
	return 0;
}

/*
 * Local variables:
 * c-basic-offset: 8
 * End:
 */
