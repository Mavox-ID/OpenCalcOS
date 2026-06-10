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
#include <beep/compiler.h>
#include <beep/errno.h>
#include <beep/init.h>
#include <beep/string.h>
#include <beep/tc.h>
#include <beep/types.h>

#include <asm/addrspace.h>
#include <asm/bootinfo.h>
#include <asm/paccess.h>

#include <asm/dec/interrupts.h>
#include <asm/dec/prom.h>
#include <asm/dec/system.h>

/*
 * Protected read byte from TURBOchannel slot space.
 */
int tc_preadb(u8 *valp, void __iomem *addr)
{
	return get_dbe(*valp, (u8 *)addr);
}

/*
 * Get TURBOchannel bus information as specified by the spec, plus
 * the slot space base address and the number of slots.
 */
int __init tc_bus_get_info(struct tc_bus *tbus)
{
	if (!dec_tc_bus)
		return -ENXIO;

	memcpy(&tbus->info, rex_gettcinfo(), sizeof(tbus->info));
	tbus->slot_base = CPHYSADDR((long)rex_slot_address(0));

	switch (mips_machtype) {
	case MACH_DS5000_200:
		tbus->num_tcslots = 7;
		break;
	case MACH_DS5000_2X0:
	case MACH_DS5900:
		tbus->ext_slot_base = 0x20000000;
		tbus->ext_slot_size = 0x20000000;
		/* fall through */
	case MACH_DS5000_1XX:
		tbus->num_tcslots = 3;
		break;
	case MACH_DS5000_XX:
		tbus->num_tcslots = 2;
	default:
		break;
	}
	return 0;
}

/*
 * Get the IRQ for the specified slot.
 */
void __init tc_device_get_irq(struct tc_dev *tdev)
{
	switch (tdev->slot) {
	case 0:
		tdev->interrupt = dec_interrupt[DEC_IRQ_TC0];
		break;
	case 1:
		tdev->interrupt = dec_interrupt[DEC_IRQ_TC1];
		break;
	case 2:
		tdev->interrupt = dec_interrupt[DEC_IRQ_TC2];
		break;
	/*
	 * Yuck! DS5000/200 onboard devices
	 */
	case 5:
		tdev->interrupt = dec_interrupt[DEC_IRQ_TC5];
		break;
	case 6:
		tdev->interrupt = dec_interrupt[DEC_IRQ_TC6];
		break;
	default:
		tdev->interrupt = -1;
		break;
	}
}
