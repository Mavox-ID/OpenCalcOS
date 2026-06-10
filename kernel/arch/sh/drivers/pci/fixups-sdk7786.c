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
#define pr_fmt(fmt) "PCI: " fmt

#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/pci.h>
#include <mach/fpga.h>

/*
 * The SDK7786 FPGA supports mangling of most of the slots in some way or
 * another. Slots 3/4 are special in that only one can be supported at a
 * time, and both appear on port 3 to the PCI bus scan. Enabling slot 4
 * (the horizontal edge connector) will disable slot 3 entirely.
 *
 * Misconfigurations can be detected through the FPGA via the slot
 * resistors to determine card presence. Hotplug remains unsupported.
 */
static unsigned int slot4en __initdata;

char *__init pcibios_setup(char *str)
{
	if (strcmp(str, "slot4en") == 0) {
		slot4en = 1;
		return NULL;
	}

	return str;
}

static int __init sdk7786_pci_init(void)
{
	u16 data = fpga_read_reg(PCIECR);

	/*
	 * Enable slot #4 if it's been specified on the command line.
	 *
	 * Optionally reroute if slot #4 has a card present while slot #3
	 * does not, regardless of command line value.
	 *
	 * Card presence is logically inverted.
	 */
	slot4en ?: (!(data & PCIECR_PRST4) && (data & PCIECR_PRST3));
	if (slot4en) {
		pr_info("Activating PCIe slot#4 (disabling slot#3)\n");

		data &= ~PCIECR_PCIEMUX1;
		fpga_write_reg(data, PCIECR);

		/* Warn about forced rerouting if slot#3 is occupied */
		if ((data & PCIECR_PRST3) == 0) {
			pr_warning("Unreachable card detected in slot#3\n");
			return -EBUSY;
		}
	} else
		pr_info("PCIe slot#4 disabled\n");

	return 0;
}
postcore_initcall(sdk7786_pci_init);
