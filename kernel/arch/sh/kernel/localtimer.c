/*
 * Dummy local timer
 *
 * Copyright (C) 2008  Paul Mundt
 *
 * cloned from:
 *
 *  beep/arch/arm/mach-realview/localtimer.c
 *
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/delay.h>
#include <beep/device.h>
#include <beep/smp.h>
#include <beep/jiffies.h>
#include <beep/percpu.h>
#include <beep/clockchips.h>
#include <beep/hardirq.h>
#include <beep/irq.h>

static DEFINE_PER_CPU(struct clock_event_device, local_clockevent);

/*
 * Used on SMP for either the local timer or SMP_MSG_TIMER
 */
void local_timer_interrupt(void)
{
	struct clock_event_device *clk = &__get_cpu_var(local_clockevent);

	irq_enter();
	clk->event_handler(clk);
	irq_exit();
}

static void dummy_timer_set_mode(enum clock_event_mode mode,
				 struct clock_event_device *clk)
{
}

void local_timer_setup(unsigned int cpu)
{
	struct clock_event_device *clk = &per_cpu(local_clockevent, cpu);

	clk->name		= "dummy_timer";
	clk->features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_DUMMY;
	clk->rating		= 400;
	clk->mult		= 1;
	clk->set_mode		= dummy_timer_set_mode;
	clk->broadcast		= smp_timer_broadcast;
	clk->cpumask		= cpumask_of(cpu);

	clockevents_register_device(clk);
}

void local_timer_stop(unsigned int cpu)
{
}
