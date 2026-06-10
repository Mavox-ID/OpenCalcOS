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
#include <beep/sched.h>
#include <beep/kernel.h>
#include <beep/param.h>
#include <beep/interrupt.h>
#include <beep/init.h>
#include <beep/irq.h>
#include <beep/pci.h>
#include <beep/module.h>
#include <beep/io.h>
#include <mach/pci.h>

/*
 * The !gapspci_config_access case really shouldn't happen, ever, unless
 * someone implicitly messes around with the last devfn value.. otherwise we
 * only support a single device anyways, and if we didn't have a BBA, we
 * wouldn't make it terribly far through the PCI setup anyways.
 *
 * Also, we could very easily support both Type 0 and Type 1 configurations
 * here, but since it doesn't seem that there is any such implementation in
 * existence, we don't bother.
 *
 * I suppose if someone actually gets around to ripping the chip out of
 * the BBA and hanging some more devices off of it, then this might be
 * something to take into consideration. However, due to the cost of the BBA,
 * and the general lack of activity by DC hardware hackers, this doesn't seem
 * likely to happen anytime soon.
 */
static int gapspci_config_access(unsigned char bus, unsigned int devfn)
{
	return (bus == 0) && (devfn == 0);
}

/*
 * We can also actually read and write in b/w/l sizes! Thankfully this part
 * was at least done right, and we don't have to do the stupid masking and
 * shifting that we do on the 7751! Small wonders never cease to amaze.
 */
static int gapspci_read(struct pci_bus *bus, unsigned int devfn, int where, int size, u32 *val)
{
	*val = 0xffffffff;

	if (!gapspci_config_access(bus->number, devfn))
		return PCIBIOS_DEVICE_NOT_FOUND;

	switch (size) {
	case 1: *val = inb(GAPSPCI_BBA_CONFIG+where); break;
	case 2: *val = inw(GAPSPCI_BBA_CONFIG+where); break;
	case 4: *val = inl(GAPSPCI_BBA_CONFIG+where); break;
	}

        return PCIBIOS_SUCCESSFUL;
}

static int gapspci_write(struct pci_bus *bus, unsigned int devfn, int where, int size, u32 val)
{
	if (!gapspci_config_access(bus->number, devfn))
		return PCIBIOS_DEVICE_NOT_FOUND;

	switch (size) {
	case 1: outb(( u8)val, GAPSPCI_BBA_CONFIG+where); break;
	case 2: outw((u16)val, GAPSPCI_BBA_CONFIG+where); break;
	case 4: outl((u32)val, GAPSPCI_BBA_CONFIG+where); break;
	}

        return PCIBIOS_SUCCESSFUL;
}

struct pci_ops gapspci_pci_ops = {
	.read	= gapspci_read,
	.write	= gapspci_write,
};
