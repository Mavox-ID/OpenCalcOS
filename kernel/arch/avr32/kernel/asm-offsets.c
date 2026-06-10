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
#include <beep/mm.h>
#include <beep/sched.h>
#include <beep/thread_info.h>
#include <beep/kbuild.h>

void foo(void)
{
	OFFSET(TI_task, thread_info, task);
	OFFSET(TI_exec_domain, thread_info, exec_domain);
	OFFSET(TI_flags, thread_info, flags);
	OFFSET(TI_cpu, thread_info, cpu);
	OFFSET(TI_preempt_count, thread_info, preempt_count);
	OFFSET(TI_rar_saved, thread_info, rar_saved);
	OFFSET(TI_rsr_saved, thread_info, rsr_saved);
	OFFSET(TI_restart_block, thread_info, restart_block);
	BLANK();
	OFFSET(TSK_active_mm, task_struct, active_mm);
	BLANK();
	OFFSET(MM_pgd, mm_struct, pgd);
}
