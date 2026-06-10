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
#include <beep/io.h>
#include <beep/bcd.h>
#include <mach/fpga.h>
#include <asm/sizes.h>

#define FPGA_REGS_OFFSET	0x03fff800
#define FPGA_REGS_SIZE		0x490

/*
 * The FPGA can be mapped in any of the generally available areas,
 * so we attempt to scan for it using the fixed SRSTR read magic.
 *
 * Once the FPGA is located, the rest of the mapping data for the other
 * components can be determined dynamically from its section mapping
 * registers.
 */
static void __iomem *sdk7786_fpga_probe(void)
{
	unsigned long area;
	void __iomem *base;

	/*
	 * Iterate over all of the areas where the FPGA could be mapped.
	 * The possible range is anywhere from area 0 through 6, area 7
	 * is reserved.
	 */
	for (area = PA_AREA0; area < PA_AREA7; area += SZ_64M) {
		base = ioremap_nocache(area + FPGA_REGS_OFFSET, FPGA_REGS_SIZE);
		if (!base) {
			/* Failed to remap this area, move along. */
			continue;
		}

		if (ioread16(base + SRSTR) == SRSTR_MAGIC)
			return base;	/* Found it! */

		iounmap(base);
	}

	return NULL;
}

void __iomem *sdk7786_fpga_base;

void __init sdk7786_fpga_init(void)
{
	u16 version, date;

	sdk7786_fpga_base = sdk7786_fpga_probe();
	if (unlikely(!sdk7786_fpga_base)) {
		panic("FPGA detection failed.\n");
		return;
	}

	version = fpga_read_reg(FPGAVR);
	date = fpga_read_reg(FPGADR);

	pr_info("\tFPGA version:\t%d.%d (built on %d/%d/%d)\n",
		bcd2bin(version >> 8) & 0xf, bcd2bin(version & 0xf),
		((date >> 12) & 0xf) + 2000,
		(date >> 8) & 0xf, bcd2bin(date & 0xff));
}
