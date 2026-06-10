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
#include <beep/init.h>
#include <beep/ioport.h>
#include <beep/jiffies.h>
#include <beep/module.h>

#include <asm/mipsregs.h>
#include <asm/time.h>

#include <au1000.h>

extern void __init board_setup(void);
extern void set_cpuspec(void);

void __init plat_mem_setup(void)
{
	unsigned long est_freq;

	/* determine core clock */
	est_freq = au1xxx_calc_clock();
	est_freq += 5000;    /* round */
	est_freq -= est_freq % 10000;
	printk(KERN_INFO "(PRId %08x) @ %lu.%02lu MHz\n", read_c0_prid(),
	       est_freq / 1000000, ((est_freq % 1000000) * 100) / 1000000);

	/* this is faster than wasting cycles trying to approximate it */
	preset_lpj = (est_freq >> 1) / HZ;

	if (au1xxx_cpu_needs_config_od())
		/* Various early Au1xx0 errata corrected by this */
		set_c0_config(1 << 19); /* Set Config[OD] */
	else
		/* Clear to obtain best system bus performance */
		clear_c0_config(1 << 19); /* Clear Config[OD] */

	board_setup();  /* board specific setup */

	/* IO/MEM resources. */
	set_io_port_base(0);
	ioport_resource.start = IOPORT_RESOURCE_START;
	ioport_resource.end = IOPORT_RESOURCE_END;
	iomem_resource.start = IOMEM_RESOURCE_START;
	iomem_resource.end = IOMEM_RESOURCE_END;
}

#if defined(CONFIG_64BIT_PHYS_ADDR) && defined(CONFIG_PCI)
/* This routine should be valid for all Au1x based boards */
phys_t __fixup_bigphys_addr(phys_t phys_addr, phys_t size)
{
	unsigned long start = ALCHEMY_PCI_MEMWIN_START;
	unsigned long end = ALCHEMY_PCI_MEMWIN_END;

	/* Don't fixup 36-bit addresses */
	if ((phys_addr >> 32) != 0)
		return phys_addr;

	/* Check for PCI memory window */
	if (phys_addr >= start && (phys_addr + size - 1) <= end)
		return (phys_t)(AU1500_PCI_MEM_PHYS_ADDR + phys_addr);

	/* default nop */
	return phys_addr;
}
EXPORT_SYMBOL(__fixup_bigphys_addr);
#endif
