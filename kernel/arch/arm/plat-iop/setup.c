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
#include <beep/mm.h>
#include <beep/init.h>
#include <asm/mach/map.h>
#include <asm/hardware/iop3xx.h>

/*
 * Standard IO mapping for all IOP3xx based systems.  Note that
 * the IOP3xx OCCDR must be mapped uncached and unbuffered.
 */
static struct map_desc iop3xx_std_desc[] __initdata = {
	 {	/* mem mapped registers */
		.virtual	= IOP3XX_PERIPHERAL_VIRT_BASE,
		.pfn		= __phys_to_pfn(IOP3XX_PERIPHERAL_PHYS_BASE),
		.length		= IOP3XX_PERIPHERAL_SIZE,
		.type		= MT_UNCACHED,
	 },
};

void __init iop3xx_map_io(void)
{
	iotable_init(iop3xx_std_desc, ARRAY_SIZE(iop3xx_std_desc));
}
