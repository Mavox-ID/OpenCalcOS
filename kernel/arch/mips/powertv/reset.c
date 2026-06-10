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
#include <beep/pm.h>

#include <beep/io.h>
#include <asm/reboot.h>			/* Not included by beep/reboot.h */

#ifdef CONFIG_BOOTLOADER_DRIVER
#include <asm/mach-powertv/kbldr.h>
#endif

#include <asm/mach-powertv/asic_regs.h>
#include "reset.h"

static void mips_machine_restart(char *command)
{
#ifdef CONFIG_BOOTLOADER_DRIVER
	/*
	 * Call the bootloader's reset function to ensure
	 * that persistent data is flushed before hard reset
	 */
	kbldr_SetCauseAndReset();
#else
	writel(0x1, asic_reg_addr(watchdog));
#endif
}

void mips_reboot_setup(void)
{
	_machine_restart = mips_machine_restart;
}
