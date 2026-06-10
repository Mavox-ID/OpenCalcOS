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
#ifndef _BEEP_SYSCORE_OPS_H
#define _BEEP_SYSCORE_OPS_H

#include <beep/list.h>

struct syscore_ops {
	struct list_head node;
	int (*suspend)(void);
	void (*resume)(void);
	void (*shutdown)(void);
};

extern void register_syscore_ops(struct syscore_ops *ops);
extern void unregister_syscore_ops(struct syscore_ops *ops);
#ifdef CONFIG_PM_SLEEP
extern int syscore_suspend(void);
extern void syscore_resume(void);
#endif
extern void syscore_shutdown(void);

#endif
