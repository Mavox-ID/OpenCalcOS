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

#define NUM_GPRS 16

static const char *gpr_names[NUM_GPRS] = {
	"%r0", "%r1",  "%r2",  "%r3",  "%r4",  "%r5",  "%r6",  "%r7",
	"%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15",
};

const char *get_arch_regstr(unsigned int n)
{
	return (n >= NUM_GPRS) ? NULL : gpr_names[n];
}
