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
#include <libio.h>
#include <dwarf-regs.h>

/*
 * Generic dwarf analysis helpers
 */

#define X86_32_MAX_REGS 8
const char *x86_32_regs_table[X86_32_MAX_REGS] = {
	"%ax",
	"%cx",
	"%dx",
	"%bx",
	"$stack",	/* Stack address instead of %sp */
	"%bp",
	"%si",
	"%di",
};

#define X86_64_MAX_REGS 16
const char *x86_64_regs_table[X86_64_MAX_REGS] = {
	"%ax",
	"%dx",
	"%cx",
	"%bx",
	"%si",
	"%di",
	"%bp",
	"%sp",
	"%r8",
	"%r9",
	"%r10",
	"%r11",
	"%r12",
	"%r13",
	"%r14",
	"%r15",
};

/* TODO: switching by dwarf address size */
#ifdef __x86_64__
#define ARCH_MAX_REGS X86_64_MAX_REGS
#define arch_regs_table x86_64_regs_table
#else
#define ARCH_MAX_REGS X86_32_MAX_REGS
#define arch_regs_table x86_32_regs_table
#endif

/* Return architecture dependent register string (for kprobe-tracer) */
const char *get_arch_regstr(unsigned int n)
{
	return (n <= ARCH_MAX_REGS) ? arch_regs_table[n] : NULL;
}
