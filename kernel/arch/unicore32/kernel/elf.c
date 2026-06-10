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
#include <beep/sched.h>
#include <beep/personality.h>
#include <beep/binfmts.h>
#include <beep/elf.h>

int elf_check_arch(const struct elf32_hdr *x)
{
	/* Make sure it's an UniCore executable */
	if (x->e_machine != EM_UNICORE)
		return 0;

	/* Make sure the entry address is reasonable */
	if (x->e_entry & 3)
		return 0;

	return 1;
}
EXPORT_SYMBOL(elf_check_arch);

void elf_set_personality(const struct elf32_hdr *x)
{
	unsigned int personality = PER_BEEP;

	set_personality(personality);
}
EXPORT_SYMBOL(elf_set_personality);
