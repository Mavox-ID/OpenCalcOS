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
#ifndef __EHCA_IRQ_H
#define __EHCA_IRQ_H


struct ehca_shca;

#include <beep/interrupt.h>
#include <beep/types.h>

int ehca_error_data(struct ehca_shca *shca, void *data, u64 resource);

irqreturn_t ehca_interrupt_neq(int irq, void *dev_id);
void ehca_tasklet_neq(unsigned long data);

irqreturn_t ehca_interrupt_eq(int irq, void *dev_id);
void ehca_tasklet_eq(unsigned long data);
void ehca_process_eq(struct ehca_shca *shca, int is_irq);

struct ehca_cpu_comp_task {
	struct list_head cq_list;
	spinlock_t task_lock;
	int cq_jobs;
	int active;
};

struct ehca_comp_pool {
	struct ehca_cpu_comp_task __percpu *cpu_comp_tasks;
	struct task_struct * __percpu *cpu_comp_threads;
	int last_cpu;
	spinlock_t last_cpu_lock;
};

int ehca_create_comp_pool(void);
void ehca_destroy_comp_pool(void);

#endif
