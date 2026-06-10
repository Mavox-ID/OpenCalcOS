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
#include <asm/processor.h>

static void putc(char c);

static int puts(const char *s)
{
	char c;
	while ((c = *s++)) putc(c);
	return 0;
}

#if defined(CONFIG_PLAT_M32700UT) || defined(CONFIG_PLAT_OPSPUT)
#include <asm/m32r.h>
#include <asm/io.h>

#define USE_FPGA_MAP	0

#if USE_FPGA_MAP
/*
 * fpga configuration program uses MMU, and define map as same as
 * M32104 uT-Engine board.
 */
#define BOOT_SIO0STS	(volatile unsigned short *)(0x02c00000 + 0x20006)
#define BOOT_SIO0TXB	(volatile unsigned short *)(0x02c00000 + 0x2000c)
#else
#undef PLD_BASE
#if defined(CONFIG_PLAT_OPSPUT)
#define PLD_BASE	0x1cc00000
#else
#define PLD_BASE	0xa4c00000
#endif
#define BOOT_SIO0STS	PLD_ESIO0STS
#define BOOT_SIO0TXB	PLD_ESIO0TXB
#endif

static void putc(char c)
{
	while ((*BOOT_SIO0STS & 0x3) != 0x3)
		cpu_relax();
	if (c == '\n') {
		*BOOT_SIO0TXB = '\r';
		while ((*BOOT_SIO0STS & 0x3) != 0x3)
			cpu_relax();
	}
	*BOOT_SIO0TXB = c;
}
#else /* !(CONFIG_PLAT_M32700UT) */
#if defined(CONFIG_PLAT_MAPPI2)
#define SIO0STS	(volatile unsigned short *)(0xa0efd000 + 14)
#define SIO0TXB	(volatile unsigned short *)(0xa0efd000 + 30)
#else
#define SIO0STS	(volatile unsigned short *)(0x00efd000 + 14)
#define SIO0TXB	(volatile unsigned short *)(0x00efd000 + 30)
#endif

static void putc(char c)
{
	while ((*SIO0STS & 0x1) == 0)
		cpu_relax();
	if (c == '\n') {
		*SIO0TXB = '\r';
		while ((*SIO0STS & 0x1) == 0)
			cpu_relax();
	}
	*SIO0TXB = c;
}
#endif
