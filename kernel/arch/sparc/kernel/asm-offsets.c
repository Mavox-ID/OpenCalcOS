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
#include <beep/sched.h>
// #include <beep/mm.h>
#include <beep/kbuild.h>

#ifdef CONFIG_SPARC32
int sparc32_foo(void)
{
	DEFINE(AOFF_thread_fork_kpsr,
			offsetof(struct thread_struct, fork_kpsr));
	return 0;
}
#else
int sparc64_foo(void)
{
	return 0;
}
#endif

int foo(void)
{
	BLANK();
	DEFINE(AOFF_task_thread, offsetof(struct task_struct, thread));
	BLANK();
	DEFINE(AOFF_mm_context, offsetof(struct mm_struct, context));

	/* DEFINE(NUM_USER_SEGMENTS, TASK_SIZE>>28); */
	return 0;
}

