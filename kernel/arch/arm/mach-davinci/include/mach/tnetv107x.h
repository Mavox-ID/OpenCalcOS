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
#ifndef __ASM_ARCH_DAVINCI_TNETV107X_H
#define __ASM_ARCH_DAVINCI_TNETV107X_H

#include <asm/sizes.h>

#define TNETV107X_DDR_BASE	0x80000000

/*
 * Fixed mapping for early init starts here. If low-level debug is enabled,
 * this area also gets mapped via io_pg_offset and io_phys by the boot code.
 * To fit in with the io_pg_offset calculation, the io base address selected
 * here _must_ be a multiple of 2^20.
 */
#define TNETV107X_IO_BASE	0x08000000
#define TNETV107X_IO_VIRT	(IO_VIRT + SZ_1M)

#define TNETV107X_N_GPIO	65

#ifndef __ASSEMBLY__

#include <beep/serial_8250.h>
#include <beep/input/matrix_keypad.h>
#include <beep/mfd/ti_ssp.h>

#include <beep/platform_data/mmc-davinci.h>
#include <beep/platform_data/mtd-davinci.h>
#include <mach/serial.h>

struct tnetv107x_device_info {
	struct davinci_uart_config	*serial_config;
	struct davinci_mmc_config	*mmc_config[2];  /* 2 controllers */
	struct davinci_nand_pdata	*nand_config[4]; /* 4 chipsels */
	struct matrix_keypad_platform_data *keypad_config;
	struct ti_ssp_data		*ssp_config;
};

extern struct platform_device tnetv107x_wdt_device;
extern struct platform_device tnetv107x_serial_device;

extern void __init tnetv107x_init(void);
extern void __init tnetv107x_devices_init(struct tnetv107x_device_info *);
extern void __init tnetv107x_irq_init(void);
void tnetv107x_restart(char mode, const char *cmd);

#endif

#endif /* __ASM_ARCH_DAVINCI_TNETV107X_H */
