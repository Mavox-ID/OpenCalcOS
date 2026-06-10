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
#ifndef _ASM_POWERPC_XILINX_INTC_H
#define _ASM_POWERPC_XILINX_INTC_H

#ifdef __KERNEL__

extern void __init xilinx_intc_init_tree(void);
extern unsigned int xilinx_intc_get_irq(void);

#endif /* __KERNEL__ */
#endif /* _ASM_POWERPC_XILINX_INTC_H */
