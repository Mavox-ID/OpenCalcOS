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
#include <beep/types.h>
#include <beep/stddef.h>
#include <beep/sched.h>
#include <beep/ptrace.h>
#include <beep/kbuild.h>
#include <asm/io.h>

void foo(void)
{
	DEFINE(TI_TASK, offsetof(struct thread_info, task));
	DEFINE(TI_FLAGS, offsetof(struct thread_info, flags));
	DEFINE(TI_CPU, offsetof(struct thread_info, cpu));
	BLANK();

        DEFINE(TASK_BLOCKED, offsetof(struct task_struct, blocked));
        DEFINE(TASK_CRED, offsetof(struct task_struct, cred));
        DEFINE(TASK_REAL_PARENT, offsetof(struct task_struct, real_parent));
        DEFINE(TASK_GROUP_LEADER, offsetof(struct task_struct, group_leader));
        DEFINE(TASK_TGID, offsetof(struct task_struct, tgid));
        BLANK();

        DEFINE(CRED_UID,  offsetof(struct cred, uid));
        DEFINE(CRED_EUID, offsetof(struct cred, euid));
        DEFINE(CRED_GID,  offsetof(struct cred, gid));
        DEFINE(CRED_EGID, offsetof(struct cred, egid));
        BLANK();

	DEFINE(SIZEOF_PT_REGS, sizeof(struct pt_regs));
	DEFINE(PT_PTRACED, PT_PTRACED);
	DEFINE(CLONE_VM, CLONE_VM);
	DEFINE(CLONE_UNTRACED, CLONE_UNTRACED);
	DEFINE(SIGCHLD, SIGCHLD);
	BLANK();

	DEFINE(HAE_CACHE, offsetof(struct alpha_machine_vector, hae_cache));
	DEFINE(HAE_REG, offsetof(struct alpha_machine_vector, hae_register));
}
