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
#include <beep/bootmem.h>

#include <loongson.h>

/* Loongson CPU address windows config space base address */
unsigned long __maybe_unused _loongson_addrwincfg_base;

void __init prom_init(void)
{
	/* init base address of io space */
	set_io_port_base((unsigned long)
		ioremap(LOONGSON_PCIIO_BASE, LOONGSON_PCIIO_SIZE));

#ifdef CONFIG_CPU_SUPPORTS_ADDRWINCFG
	_loongson_addrwincfg_base = (unsigned long)
		ioremap(LOONGSON_ADDRWINCFG_BASE, LOONGSON_ADDRWINCFG_SIZE);
#endif

	prom_init_cmdline();
	prom_init_env();
	prom_init_memory();

	/*init the uart base address */
	prom_init_uart_base();
}

void __init prom_free_prom_memory(void)
{
}
