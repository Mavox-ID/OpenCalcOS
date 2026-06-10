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
#ifndef	__MACH_PATA_PXA_H__
#define	__MACH_PATA_PXA_H__

struct pata_pxa_pdata {
	/* PXA DMA DREQ<0:2> pin */
	uint32_t	dma_dreq;
	/* Register shift */
	uint32_t	reg_shift;
	/* IRQ flags */
	uint32_t	irq_flags;
};

#endif	/* __MACH_PATA_PXA_H__ */
