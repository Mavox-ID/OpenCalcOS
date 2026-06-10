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
#include <beep/mm.h>
#include <beep/sched.h>
#include <beep/bootmem.h>
#include <asm/addrspace.h>
#include <asm/bootinfo.h>
#include <beep/string.h>
#include <beep/kernel.h>

int prom_argc;
char **prom_argv, **prom_envp;
extern void  __init prom_init_cmdline(void);
extern char *prom_getenv(char *envname);

const char *get_system_type(void)
{
	return "NXP PNX8550/JBS";
}

void __init prom_init(void)
{
	unsigned long memsize;

	//memsize = 0x02800000; /* Trimedia uses memory above */
	memsize = 0x08000000; /* Trimedia uses memory above */
	add_memory_region(0, memsize, BOOT_MEM_RAM);
}
