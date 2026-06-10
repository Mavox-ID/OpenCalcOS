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
#ifndef __MICROBLAZE_UNWIND_H
#define __MICROBLAZE_UNWIND_H

struct stack_trace;

struct trap_handler_info {
	unsigned long start_addr;
	unsigned long end_addr;
	const char    *trap_name;
};
extern struct trap_handler_info microblaze_trap_handlers;

extern const char _hw_exception_handler;
extern const char ex_handler_unhandled;

void microblaze_unwind(struct task_struct *task, struct stack_trace *trace);

#endif	/* __MICROBLAZE_UNWIND_H */

