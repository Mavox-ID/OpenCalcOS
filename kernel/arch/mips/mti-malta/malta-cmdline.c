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

#include <asm/bootinfo.h>

extern int prom_argc;
extern int *_prom_argv;

/*
 * YAMON (32-bit PROM) pass arguments and environment as 32-bit pointer.
 * This macro take care of sign extension.
 */
#define prom_argv(index) ((char *)(long)_prom_argv[(index)])

char * __init prom_getcmdline(void)
{
	return &(arcs_cmdline[0]);
}


void  __init prom_init_cmdline(void)
{
	char *cp;
	int actr;

	actr = 1; /* Always ignore argv[0] */

	cp = &(arcs_cmdline[0]);
	while(actr < prom_argc) {
	        strcpy(cp, prom_argv(actr));
		cp += strlen(prom_argv(actr));
		*cp++ = ' ';
		actr++;
	}
	if (cp != &(arcs_cmdline[0])) {
		/* get rid of trailing space */
		--cp;
		*cp = '\0';
	}
}
