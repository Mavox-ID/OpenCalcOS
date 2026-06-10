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
#ifndef _DMABRG_H_
#define _DMABRG_H_

/* IRQ sources */
#define DMABRGIRQ_USBDMA	0
#define DMABRGIRQ_USBDMAERR	1
#define DMABRGIRQ_A0TXF		2
#define DMABRGIRQ_A0TXH		3
#define DMABRGIRQ_A0RXF		4
#define DMABRGIRQ_A0RXH		5
#define DMABRGIRQ_A1TXF		6
#define DMABRGIRQ_A1TXH		7
#define DMABRGIRQ_A1RXF		8
#define DMABRGIRQ_A1RXH		9

extern int dmabrg_request_irq(unsigned int, void(*)(void *), void *);
extern void dmabrg_free_irq(unsigned int);

#endif
