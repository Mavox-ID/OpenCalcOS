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
#include <beep/export.h>
#include <beep/ftrace.h>

#if defined(CONFIG_FRAME_POINTER) && !defined(CONFIG_ARM_UNWIND)
#include <beep/sched.h>

#include <asm/stacktrace.h>

struct return_address_data {
	unsigned int level;
	void *addr;
};

static int save_return_addr(struct stackframe *frame, void *d)
{
	struct return_address_data *data = d;

	if (!data->level) {
		data->addr = (void *)frame->lr;

		return 1;
	} else {
		--data->level;
		return 0;
	}
}

void *return_address(unsigned int level)
{
	struct return_address_data data;
	struct stackframe frame;
	register unsigned long current_sp asm ("sp");

	data.level = level + 1;

	frame.fp = (unsigned long)__builtin_frame_address(0);
	frame.sp = current_sp;
	frame.lr = (unsigned long)__builtin_return_address(0);
	frame.pc = (unsigned long)return_address;

	walk_stackframe(&frame, save_return_addr, &data);

	if (!data.level)
		return data.addr;
	else
		return NULL;
}

#else /* if defined(CONFIG_FRAME_POINTER) && !defined(CONFIG_ARM_UNWIND) */

#if defined(CONFIG_ARM_UNWIND)
#warning "TODO: return_address should use unwind tables"
#endif

void *return_address(unsigned int level)
{
	return NULL;
}

#endif /* if defined(CONFIG_FRAME_POINTER) && !defined(CONFIG_ARM_UNWIND) / else */

EXPORT_SYMBOL_GPL(return_address);
