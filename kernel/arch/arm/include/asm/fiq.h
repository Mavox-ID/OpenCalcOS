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
#ifndef __ASM_FIQ_H
#define __ASM_FIQ_H

#include <asm/ptrace.h>

struct fiq_handler {
	struct fiq_handler *next;
	/* Name
	 */
	const char *name;
	/* Called to ask driver to relinquish/
	 * reacquire FIQ
	 * return zero to accept, or -<errno>
	 */
	int (*fiq_op)(void *, int relinquish);
	/* data for the relinquish/reacquire functions
	 */
	void *dev_id;
};

extern int claim_fiq(struct fiq_handler *f);
extern void release_fiq(struct fiq_handler *f);
extern void set_fiq_handler(void *start, unsigned int length);
extern void enable_fiq(int fiq);
extern void disable_fiq(int fiq);

/* helpers defined in fiqasm.S: */
extern void __set_fiq_regs(unsigned long const *regs);
extern void __get_fiq_regs(unsigned long *regs);

static inline void set_fiq_regs(struct pt_regs const *regs)
{
	__set_fiq_regs(&regs->ARM_r8);
}

static inline void get_fiq_regs(struct pt_regs *regs)
{
	__get_fiq_regs(&regs->ARM_r8);
}

#endif
