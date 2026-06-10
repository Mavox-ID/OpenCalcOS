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
#include <beep/sched.h>
#include <beep/smp.h>
#include <beep/interrupt.h>
#include <beep/kernel_stat.h>
#include <beep/delay.h>
#include <beep/init.h>
#include <beep/spinlock.h>

#include <asm/ptrace.h>
#include <beep/atomic.h>
#include <asm/irq.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/sections.h>
#include <asm/io.h>
#include <asm/prom.h>
#include <asm/smp.h>
#include <asm/machdep.h>
#include <asm/mpic.h>
#include <asm/rtas.h>

static int smp_chrp_kick_cpu(int nr)
{
	*(unsigned long *)KERNELBASE = nr;
	asm volatile("dcbf 0,%0"::"r"(KERNELBASE):"memory");

	return 0;
}

static void smp_chrp_setup_cpu(int cpu_nr)
{
	mpic_setup_this_cpu();
}

/* CHRP with openpic */
struct smp_ops_t chrp_smp_ops = {
	.message_pass = smp_mpic_message_pass,
	.probe = smp_mpic_probe,
	.kick_cpu = smp_chrp_kick_cpu,
	.setup_cpu = smp_chrp_setup_cpu,
	.give_timebase = rtas_give_timebase,
	.take_timebase = rtas_take_timebase,
};
