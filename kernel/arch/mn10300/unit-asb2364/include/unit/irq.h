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
#ifndef _UNIT_IRQ_H
#define _UNIT_IRQ_H

#ifndef __ASSEMBLY__

#ifdef CONFIG_SMP
#define NR_CPU_IRQS	GxICR_NUM_EXT_IRQS
#else
#define NR_CPU_IRQS	GxICR_NUM_IRQS
#endif

enum {
	FPGA_LAN_IRQ	= NR_CPU_IRQS,
	FPGA_UART_IRQ,
	FPGA_I2C_IRQ,
	FPGA_USB_IRQ,
	FPGA_RESERVED_IRQ,
	FPGA_FPGA_IRQ,
	NR_IRQS
};

extern void __init irq_fpga_init(void);

#endif /* !__ASSEMBLY__ */
#endif /* _UNIT_IRQ_H */
