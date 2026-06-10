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
#include <beep/device.h>
#include <beep/types.h>
#include <beep/gpio.h>
#include <beep/vme.h>

#include "vme_pio2.h"

static int pio2_cntr_irq_set(struct pio2_card *card, int id)
{
	int retval;
	u8 data;

	data = PIO2_CNTR_SC_DEV[id] | PIO2_CNTR_RW_BOTH | card->cntr[id].mode;
	retval = vme_master_write(card->window, &data, 1, PIO2_CNTR_CTRL[id]);
	if (retval < 0)
		return retval;

	data = card->cntr[id].count & 0xFF;
	retval = vme_master_write(card->window, &data, 1, PIO2_CNTR_DATA[id]);
	if (retval < 0)
		return retval;

	data = (card->cntr[id].count >> 8) & 0xFF;
	retval = vme_master_write(card->window, &data, 1, PIO2_CNTR_DATA[id]);
	if (retval < 0)
		return retval;

	return 0;
}

int pio2_cntr_reset(struct pio2_card *card)
{
	int i, retval = 0;
	u8 reg;

	/* Clear down all timers */
	for (i = 0; i < 6; i++) {
		card->cntr[i].mode = PIO2_CNTR_MODE5;
		card->cntr[i].count = 0;
		retval = pio2_cntr_irq_set(card, i);
		if (retval < 0)
			return retval;
	}

	/* Ensure all counter interrupts are cleared */
	do {
		retval = vme_master_read(card->window, &reg, 1,
			PIO2_REGS_INT_STAT_CNTR);
		if (retval < 0)
			return retval;
	} while (reg != 0);

	return retval;
}

