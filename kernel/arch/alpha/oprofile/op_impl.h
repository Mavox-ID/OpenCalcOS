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

/* Per-counter configuration as set via oprofilefs.  */
struct op_counter_config {
	unsigned long enabled;
	unsigned long event;
	unsigned long count;
	/* Dummies because I am too lazy to hack the userspace tools.  */
	unsigned long kernel;
	unsigned long user;
	unsigned long unit_mask;
};

/* System-wide configuration as set via oprofilefs.  */
struct op_system_config {
	unsigned long enable_pal;
	unsigned long enable_kernel;
	unsigned long enable_user;
};

/* Cached values for the various performance monitoring registers.  */
struct op_register_config {
	unsigned long enable;
	unsigned long mux_select;
	unsigned long proc_mode;
	unsigned long freq;
	unsigned long reset_values;
	unsigned long need_reset;
};

/* Per-architecture configuration and hooks.  */
struct op_axp_model {
	void (*reg_setup) (struct op_register_config *,
			   struct op_counter_config *,
			   struct op_system_config *);
	void (*cpu_setup) (void *);
	void (*reset_ctr) (struct op_register_config *, unsigned long);
	void (*handle_interrupt) (unsigned long, struct pt_regs *,
				  struct op_counter_config *);
	char *cpu_type;
	unsigned char num_counters;
	unsigned char can_set_proc_mode;
};

#endif
