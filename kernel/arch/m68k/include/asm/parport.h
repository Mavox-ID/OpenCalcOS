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
#ifndef _ASM_M68K_PARPORT_H
#define _ASM_M68K_PARPORT_H 1

#define insl(port,buf,len)   isa_insb(port,buf,(len)<<2)
#define outsl(port,buf,len)  isa_outsb(port,buf,(len)<<2)

/* no dma, or IRQ autoprobing */
static int parport_pc_find_isa_ports (int autoirq, int autodma);
static int parport_pc_find_nonpci_ports (int autoirq, int autodma)
{
        if (! (MACH_IS_Q40))
	  return 0; /* count=0 */
	return parport_pc_find_isa_ports (PARPORT_IRQ_NONE, PARPORT_DMA_NONE);
}

#endif /* !(_ASM_M68K_PARPORT_H) */
