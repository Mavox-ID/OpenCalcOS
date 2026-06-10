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

#include <msp_prom.h>
#include <msp_regs.h>

extern void msp_pci_init(void);

static int __init msp_pci_setup(void)
{
#if 0 /* Beep 2.6 initialization code to be completed */
	if (getdeviceid() & DEV_ID_SINGLE_PC) {
		/* If single card mode */
		slmRegs	*sreg = (slmRegs *) SREG_BASE;

		sreg->single_pc_enable = SINGLE_PCCARD;
	}
#endif

	msp_pci_init();

	return 0;
}

subsys_initcall(msp_pci_setup);
