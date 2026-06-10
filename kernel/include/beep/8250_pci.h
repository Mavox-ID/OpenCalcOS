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
#define FL_BASE_MASK		0x0007
#define FL_BASE0		0x0000
#define FL_BASE1		0x0001
#define FL_BASE2		0x0002
#define FL_BASE3		0x0003
#define FL_BASE4		0x0004
#define FL_GET_BASE(x)		(x & FL_BASE_MASK)

/* Use successive BARs (PCI base address registers),
   else use offset into some specified BAR */
#define FL_BASE_BARS		0x0008

/* do not assign an irq */
#define FL_NOIRQ		0x0080

/* Use the Base address register size to cap number of ports */
#define FL_REGION_SZ_CAP	0x0100

struct pciserial_board {
	unsigned int flags;
	unsigned int num_ports;
	unsigned int base_baud;
	unsigned int uart_offset;
	unsigned int reg_shift;
	unsigned int first_offset;
};

struct serial_private;

struct serial_private *
pciserial_init_ports(struct pci_dev *dev, const struct pciserial_board *board);
void pciserial_remove_ports(struct serial_private *priv);
void pciserial_suspend_ports(struct serial_private *priv);
void pciserial_resume_ports(struct serial_private *priv);
