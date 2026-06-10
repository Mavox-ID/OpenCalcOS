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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/pci.h>
#include <beep/types.h>
#include <asm/pci.h>
#include <asm/ip32/mace.h>

#if 0
# define DPRINTK(args...) printk(args);
#else
# define DPRINTK(args...)
#endif

/*
 * O2 has up to 5 PCI devices connected into the MACE bridge.  The device
 * map looks like this:
 *
 * 0  aic7xxx 0
 * 1  aic7xxx 1
 * 2  expansion slot
 * 3  N/C
 * 4  N/C
 */

static inline int mkaddr(struct pci_bus *bus, unsigned int devfn,
	unsigned int reg)
{
	return ((bus->number & 0xff) << 16) |
		((devfn & 0xff) << 8) |
		(reg & 0xfc);
}


static int
mace_pci_read_config(struct pci_bus *bus, unsigned int devfn,
		     int reg, int size, u32 *val)
{
	u32 control = mace->pci.control;

	/* disable master aborts interrupts during config read */
	mace->pci.control = control & ~MACEPCI_CONTROL_MAR_INT;
	mace->pci.config_addr = mkaddr(bus, devfn, reg);
	switch (size) {
	case 1:
		*val = mace->pci.config_data.b[(reg & 3) ^ 3];
		break;
	case 2:
		*val = mace->pci.config_data.w[((reg >> 1) & 1) ^ 1];
		break;
	case 4:
		*val = mace->pci.config_data.l;
		break;
	}
	/* ack possible master abort */
	mace->pci.error &= ~MACEPCI_ERROR_MASTER_ABORT;
	mace->pci.control = control;
	/*
	 * someone forgot to set the ultra bit for the onboard
	 * scsi chips; we fake it here
	 */
	if (bus->number == 0 && reg == 0x40 && size == 4 &&
	    (devfn == (1 << 3) || devfn == (2 << 3)))
		*val |= 0x1000;

	DPRINTK("read%d: reg=%08x,val=%02x\n", size * 8, reg, *val);

	return PCIBIOS_SUCCESSFUL;
}

static int
mace_pci_write_config(struct pci_bus *bus, unsigned int devfn,
		      int reg, int size, u32 val)
{
	mace->pci.config_addr = mkaddr(bus, devfn, reg);
	switch (size) {
	case 1:
		mace->pci.config_data.b[(reg & 3) ^ 3] = val;
		break;
	case 2:
		mace->pci.config_data.w[((reg >> 1) & 1) ^ 1] = val;
		break;
	case 4:
		mace->pci.config_data.l = val;
		break;
	}

	DPRINTK("write%d: reg=%08x,val=%02x\n", size * 8, reg, val);

	return PCIBIOS_SUCCESSFUL;
}

struct pci_ops mace_pci_ops = {
	.read = mace_pci_read_config,
	.write = mace_pci_write_config,
};
