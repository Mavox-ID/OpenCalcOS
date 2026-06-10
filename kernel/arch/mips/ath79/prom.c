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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/io.h>
#include <beep/string.h>

#include <asm/bootinfo.h>
#include <asm/addrspace.h>

#include "common.h"

static inline int is_valid_ram_addr(void *addr)
{
	if (((u32) addr > KSEG0) &&
	    ((u32) addr < (KSEG0 + ATH79_MEM_SIZE_MAX)))
		return 1;

	if (((u32) addr > KSEG1) &&
	    ((u32) addr < (KSEG1 + ATH79_MEM_SIZE_MAX)))
		return 1;

	return 0;
}

static __init void ath79_prom_init_cmdline(int argc, char **argv)
{
	int i;

	if (!is_valid_ram_addr(argv))
		return;

	for (i = 0; i < argc; i++)
		if (is_valid_ram_addr(argv[i])) {
			strlcat(arcs_cmdline, " ", sizeof(arcs_cmdline));
			strlcat(arcs_cmdline, argv[i], sizeof(arcs_cmdline));
		}
}

void __init prom_init(void)
{
	ath79_prom_init_cmdline(fw_arg0, (char **)fw_arg1);
}

void __init prom_free_prom_memory(void)
{
	/* We do not have to prom memory to free */
}
