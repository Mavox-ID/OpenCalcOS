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
#include <sysdep/ptrace.h>

/* These two are from asm-um/uaccess.h and beep/module.h, check them. */
struct exception_table_entry
{
	unsigned long insn;
	unsigned long fixup;
};

const struct exception_table_entry *search_exception_tables(unsigned long add);

/* Compare this to arch/i386/mm/extable.c:fixup_exception() */
int arch_fixup(unsigned long address, struct uml_pt_regs *regs)
{
	const struct exception_table_entry *fixup;

	fixup = search_exception_tables(address);
	if (fixup != 0) {
		UPT_IP(regs) = fixup->fixup;
		return 1;
	}
	return 0;
}
