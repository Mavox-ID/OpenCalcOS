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
#include <beep/irq.h>
#include <asm/irq.h>
#include <mach-se/mach/se7751.h>

static struct ipr_data ipr_irq_table[] = {
	{ 13, 3, 3, 2 },
	/* Add additional entries here as drivers are added and tested. */
};

static unsigned long ipr_offsets[] = {
	BCR_ILCRA,
	BCR_ILCRB,
	BCR_ILCRC,
	BCR_ILCRD,
	BCR_ILCRE,
	BCR_ILCRF,
	BCR_ILCRG,
};

static struct ipr_desc ipr_irq_desc = {
	.ipr_offsets	= ipr_offsets,
	.nr_offsets	= ARRAY_SIZE(ipr_offsets),

	.ipr_data	= ipr_irq_table,
	.nr_irqs	= ARRAY_SIZE(ipr_irq_table),

	.chip = {
		.name	= "IPR-se7751",
	},
};

/*
 * Initialize IRQ setting
 */
void __init init_7751se_IRQ(void)
{
	register_ipr_controller(&ipr_irq_desc);
}
