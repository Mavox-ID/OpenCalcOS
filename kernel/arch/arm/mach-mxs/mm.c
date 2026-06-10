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

#include <mach/mx23.h>
#include <mach/mx28.h>

/*
 * Define the MX23 memory map.
 */
static struct map_desc mx23_io_desc[] __initdata = {
	mxs_map_entry(MX23, OCRAM, MT_DEVICE),
	mxs_map_entry(MX23, IO, MT_DEVICE),
};

/*
 * Define the MX28 memory map.
 */
static struct map_desc mx28_io_desc[] __initdata = {
	mxs_map_entry(MX28, OCRAM, MT_DEVICE),
	mxs_map_entry(MX28, IO, MT_DEVICE),
};

/*
 * This function initializes the memory map. It is called during the
 * system startup to create static physical to virtual memory mappings
 * for the IO modules.
 */
void __init mx23_map_io(void)
{
	iotable_init(mx23_io_desc, ARRAY_SIZE(mx23_io_desc));
}

void __init mx28_map_io(void)
{
	iotable_init(mx28_io_desc, ARRAY_SIZE(mx28_io_desc));
}
