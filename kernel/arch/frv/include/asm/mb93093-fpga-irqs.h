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
#ifndef _ASM_MB93093_FPGA_IRQS_H
#define _ASM_MB93093_FPGA_IRQS_H

#include <asm/irq.h>

#ifndef __ASSEMBLY__

/* IRQ IDs presented to drivers */
enum {
	IRQ_FPGA_PUSH_BUTTON_SW1_5		= IRQ_BASE_FPGA + 8,
	IRQ_FPGA_ROCKER_C_SW8			= IRQ_BASE_FPGA + 9,
	IRQ_FPGA_ROCKER_C_SW9			= IRQ_BASE_FPGA + 10,
};


#endif /* !__ASSEMBLY__ */

#endif /* _ASM_MB93093_FPGA_IRQS_H */
