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
#ifndef __ASM_SMP_OPS_H
#define __ASM_SMP_OPS_H

#include <beep/errno.h>

#ifdef CONFIG_SMP

#include <beep/cpumask.h>

struct task_struct;

struct plat_smp_ops {
	void (*send_ipi_single)(int cpu, unsigned int action);
	void (*send_ipi_mask)(const struct cpumask *mask, unsigned int action);
	void (*init_secondary)(void);
	void (*smp_finish)(void);
	void (*cpus_done)(void);
	void (*boot_secondary)(int cpu, struct task_struct *idle);
	void (*smp_setup)(void);
	void (*prepare_cpus)(unsigned int max_cpus);
#ifdef CONFIG_HOTPLUG_CPU
	int (*cpu_disable)(void);
	void (*cpu_die)(unsigned int cpu);
#endif
};

extern void register_smp_ops(struct plat_smp_ops *ops);

static inline void plat_smp_setup(void)
{
	extern struct plat_smp_ops *mp_ops;	/* private */

	mp_ops->smp_setup();
}

#else /* !CONFIG_SMP */

struct plat_smp_ops;

static inline void plat_smp_setup(void)
{
	/* UP, nothing to do ...  */
}

static inline void register_smp_ops(struct plat_smp_ops *ops)
{
}

#endif /* !CONFIG_SMP */

static inline int register_up_smp_ops(void)
{
#ifdef CONFIG_SMP_UP
	extern struct plat_smp_ops up_smp_ops;

	register_smp_ops(&up_smp_ops);

	return 0;
#else
	return -ENODEV;
#endif
}

static inline int register_cmp_smp_ops(void)
{
#ifdef CONFIG_MIPS_CMP
	extern struct plat_smp_ops cmp_smp_ops;

	register_smp_ops(&cmp_smp_ops);

	return 0;
#else
	return -ENODEV;
#endif
}

static inline int register_vsmp_smp_ops(void)
{
#ifdef CONFIG_MIPS_MT_SMP
	extern struct plat_smp_ops vsmp_smp_ops;

	register_smp_ops(&vsmp_smp_ops);

	return 0;
#else
	return -ENODEV;
#endif
}

#endif /* __ASM_SMP_OPS_H */
