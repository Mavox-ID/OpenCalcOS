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
#include <asm/bootinfo.h>

#include <loongson.h>

void __init prom_init_cmdline(void)
{
	int prom_argc;
	/* pmon passes arguments in 32bit pointers */
	int *_prom_argv;
	int i;
	long l;

	/* firmware arguments are initialized in head.S */
	prom_argc = fw_arg0;
	_prom_argv = (int *)fw_arg1;

	/* arg[0] is "g", the rest is boot parameters */
	arcs_cmdline[0] = '\0';
	for (i = 1; i < prom_argc; i++) {
		l = (long)_prom_argv[i];
		if (strlen(arcs_cmdline) + strlen(((char *)l) + 1)
		    >= sizeof(arcs_cmdline))
			break;
		strcat(arcs_cmdline, ((char *)l));
		strcat(arcs_cmdline, " ");
	}

	prom_init_machtype();
}
