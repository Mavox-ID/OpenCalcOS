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
#include <beep/kernel.h>
#include <beep/string.h>
#include <beep/types.h>

#include <asm/bootinfo.h>
#include <asm/dec/prom.h>

#undef PROM_DEBUG

void __init prom_init_cmdline(s32 argc, s32 *argv, u32 magic)
{
	char *arg;
	int start_arg, i;

	/*
	 * collect args and prepare cmd_line
	 */
	if (!prom_is_rex(magic))
		start_arg = 1;
	else
		start_arg = 2;
	for (i = start_arg; i < argc; i++) {
		arg = (void *)(long)(argv[i]);
		strcat(arcs_cmdline, arg);
		if (i < (argc - 1))
			strcat(arcs_cmdline, " ");
	}

#ifdef PROM_DEBUG
	printk("arcs_cmdline: %s\n", &(arcs_cmdline[0]));
#endif
}
