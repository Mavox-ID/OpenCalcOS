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
#ifndef OP_IMPL_H
#define OP_IMPL_H 1

extern int (*perf_irq)(void);

/* Per-counter configuration as set via oprofilefs.  */
struct op_counter_config {
	unsigned long enabled;
	unsigned long event;
	unsigned long count;
	/* Dummies because I am too lazy to hack the userspace tools.  */
	unsigned long kernel;
	unsigned long user;
	unsigned long exl;
	unsigned long unit_mask;
};

/* Per-architecture configury and hooks.  */
struct op_mips_model {
	void (*reg_setup) (struct op_counter_config *);
	void (*cpu_setup) (void *dummy);
	int (*init)(void);
	void (*exit)(void);
	void (*cpu_start)(void *args);
	void (*cpu_stop)(void *args);
	char *cpu_type;
	unsigned char num_counters;
};

void op_mips_backtrace(struct pt_regs * const regs, unsigned int depth);

#endif
