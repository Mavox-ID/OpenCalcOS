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
#include <beep/module.h>
#include <asm/dwarf.h>

#ifdef CONFIG_DWARF_UNWINDER

void *return_address(unsigned int depth)
{
	struct dwarf_frame *frame;
	unsigned long ra;
	int i;

	for (i = 0, frame = NULL, ra = 0; i <= depth; i++) {
		struct dwarf_frame *tmp;

		tmp = dwarf_unwind_stack(ra, frame);
		if (!tmp)
			return NULL;

		if (frame)
			dwarf_free_frame(frame);

		frame = tmp;

		if (!frame || !frame->return_addr)
			break;

		ra = frame->return_addr;
	}

	/* Failed to unwind the stack to the specified depth. */
	WARN_ON(i != depth + 1);

	if (frame)
		dwarf_free_frame(frame);

	return (void *)ra;
}

#else

void *return_address(unsigned int depth)
{
	return NULL;
}

#endif

EXPORT_SYMBOL_GPL(return_address);
