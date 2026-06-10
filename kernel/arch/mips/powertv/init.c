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
#include <beep/string.h>
#include <beep/kernel.h>

#include <asm/bootinfo.h>
#include <beep/io.h>
#include <asm/cacheflush.h>
#include <asm/traps.h>

#include <asm/mips-boards/prom.h>
#include <asm/mips-boards/generic.h>
#include <asm/mach-powertv/asic.h>

static int *_prom_envp;
unsigned long _prom_memsize;

/*
 * YAMON (32-bit PROM) pass arguments and environment as 32-bit pointer.
 * This macro take care of sign extension, if running in 64-bit mode.
 */
#define prom_envp(index) ((char *)(long)_prom_envp[(index)])

char *prom_getenv(char *envname)
{
	char *result = NULL;

	if (_prom_envp != NULL) {
		/*
		 * Return a pointer to the given environment variable.
		 * In 64-bit mode: we're using 64-bit pointers, but all pointers
		 * in the PROM structures are only 32-bit, so we need some
		 * workarounds, if we are running in 64-bit mode.
		 */
		int i, index = 0;

		i = strlen(envname);

		while (prom_envp(index)) {
			if (strncmp(envname, prom_envp(index), i) == 0) {
				result = prom_envp(index + 1);
				break;
			}
			index += 2;
		}
	}

	return result;
}

void __init prom_init(void)
{
	int prom_argc;
	char *prom_argv;

	prom_argc = fw_arg0;
	prom_argv = (char *) fw_arg1;
	_prom_envp = (int *) fw_arg2;
	_prom_memsize = (unsigned long) fw_arg3;

	if (prom_argc == 1) {
		strlcat(arcs_cmdline, " ", COMMAND_LINE_SIZE);
		strlcat(arcs_cmdline, prom_argv, COMMAND_LINE_SIZE);
	}

	configure_platform();
	prom_meminit();

#ifndef CONFIG_BOOTLOADER_DRIVER
	pr_info("\nBootloader driver isn't loaded...\n");
#endif
}
