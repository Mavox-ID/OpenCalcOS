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
#ifndef __AA_IPC_H
#define __AA_IPC_H

#include <beep/sched.h>

struct aa_profile;

int aa_may_ptrace(struct task_struct *tracer_task, struct aa_profile *tracer,
		  struct aa_profile *tracee, unsigned int mode);

int aa_ptrace(struct task_struct *tracer, struct task_struct *tracee,
	      unsigned int mode);

#endif /* __AA_IPC_H */
