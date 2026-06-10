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
#include <beep/ssb/ssb.h>
#include <asm/time.h>
#include <bcm47xx.h>

void __init plat_time_init(void)
{
	unsigned long hz = 0;

	/*
	 * Use deterministic values for initial counter interrupt
	 * so that calibrate delay avoids encountering a counter wrap.
	 */
	write_c0_count(0);
	write_c0_compare(0xffff);

	switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		hz = ssb_cpu_clock(&bcm47xx_bus.ssb.mipscore) / 2;
		break;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		hz = bcma_cpu_clock(&bcm47xx_bus.bcma.bus.drv_mips) / 2;
		break;
#endif
	}

	if (!hz)
		hz = 100000000;

	/* Set MIPS counter frequency for fixed_rate_gettimeoffset() */
	mips_hpt_frequency = hz;
}
