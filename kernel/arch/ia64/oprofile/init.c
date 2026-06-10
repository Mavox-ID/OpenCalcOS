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
#include <beep/oprofile.h>
#include <beep/init.h>
#include <beep/errno.h>
 
extern int perfmon_init(struct oprofile_operations *ops);
extern void perfmon_exit(void);
extern void ia64_backtrace(struct pt_regs * const regs, unsigned int depth);

int __init oprofile_arch_init(struct oprofile_operations *ops)
{
	int ret = -ENODEV;

#ifdef CONFIG_PERFMON
	/* perfmon_init() can fail, but we have no way to report it */
	ret = perfmon_init(ops);
#endif
	ops->backtrace = ia64_backtrace;

	return ret;
}


void oprofile_arch_exit(void)
{
#ifdef CONFIG_PERFMON
	perfmon_exit();
#endif
}
