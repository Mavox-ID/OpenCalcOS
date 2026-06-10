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
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/string.h>

#include <beep/serial_reg.h>

#include <asm/bootinfo.h>
#include <asm/mach-jz4740/base.h>

static __init void jz4740_init_cmdline(int argc, char *argv[])
{
	unsigned int count = COMMAND_LINE_SIZE - 1;
	int i;
	char *dst = &(arcs_cmdline[0]);
	char *src;

	for (i = 1; i < argc && count; ++i) {
		src = argv[i];
		while (*src && count) {
			*dst++ = *src++;
			--count;
		}
		*dst++ = ' ';
	}
	if (i > 1)
		--dst;

	*dst = 0;
}

void __init prom_init(void)
{
	jz4740_init_cmdline((int)fw_arg0, (char **)fw_arg1);
	mips_machtype = MACH_INGENIC_JZ4740;
}

void __init prom_free_prom_memory(void)
{
}

#define UART_REG(_reg) ((void __iomem *)CKSEG1ADDR(JZ4740_UART0_BASE_ADDR + (_reg << 2)))

void prom_putchar(char c)
{
	uint8_t lsr;

	do {
		lsr = readb(UART_REG(UART_LSR));
	} while ((lsr & UART_LSR_TEMT) == 0);

	writeb(c, UART_REG(UART_TX));
}
