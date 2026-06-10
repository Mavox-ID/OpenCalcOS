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
#ifndef _I8042_UNICORE32_H
#define _I8042_UNICORE32_H

#include <mach/hardware.h>

/*
 * Names.
 */
#define I8042_KBD_PHYS_DESC "isa0060/serio0"
#define I8042_AUX_PHYS_DESC "isa0060/serio1"
#define I8042_MUX_PHYS_DESC "isa0060/serio%d"

/*
 * IRQs.
 */
#define I8042_KBD_IRQ           IRQ_PS2_KBD
#define I8042_AUX_IRQ           IRQ_PS2_AUX

/*
 * Register numbers.
 */
#define I8042_COMMAND_REG	PS2_COMMAND
#define I8042_STATUS_REG	PS2_STATUS
#define I8042_DATA_REG		PS2_DATA

#define I8042_REGION_START	(resource_size_t)(PS2_DATA)
#define I8042_REGION_SIZE	(resource_size_t)(16)

static inline int i8042_read_data(void)
{
	return readb(I8042_DATA_REG);
}

static inline int i8042_read_status(void)
{
	return readb(I8042_STATUS_REG);
}

static inline void i8042_write_data(int val)
{
	writeb(val, I8042_DATA_REG);
}

static inline void i8042_write_command(int val)
{
	writeb(val, I8042_COMMAND_REG);
}

static inline int i8042_platform_init(void)
{
	if (!request_mem_region(I8042_REGION_START, I8042_REGION_SIZE, "i8042"))
		return -EBUSY;

	i8042_reset = 1;
	return 0;
}

static inline void i8042_platform_exit(void)
{
	release_mem_region(I8042_REGION_START, I8042_REGION_SIZE);
}

#endif /* _I8042_UNICORE32_H */
