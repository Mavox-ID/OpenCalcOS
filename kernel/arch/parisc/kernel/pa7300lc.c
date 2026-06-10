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
#include <beep/sched.h>
#include <beep/smp.h>
#include <beep/kernel.h>
#include <asm/io.h>
#include <asm/ptrace.h>
#include <asm/machdep.h>

/* CPU register indices */

#define MIOC_STATUS	0xf040
#define MIOC_CONTROL	0xf080
#define MDERRADD	0xf0e0
#define DMAERR		0xf0e8
#define DIOERR		0xf0ec
#define HIDMAMEM	0xf0f4

/* this returns the HPA of the CPU it was called on */
static u32 cpu_hpa(void)
{
	return 0xfffb0000;
}

static void pa7300lc_lpmc(int code, struct pt_regs *regs)
{
	u32 hpa;
	printk(KERN_WARNING "LPMC on CPU %d\n", smp_processor_id());

	show_regs(regs);

	hpa = cpu_hpa();
	printk(KERN_WARNING
		"MIOC_CONTROL %08x\n" "MIOC_STATUS  %08x\n"
		"MDERRADD     %08x\n" "DMAERR       %08x\n"
		"DIOERR       %08x\n" "HIDMAMEM     %08x\n",
		gsc_readl(hpa+MIOC_CONTROL), gsc_readl(hpa+MIOC_STATUS),
		gsc_readl(hpa+MDERRADD), gsc_readl(hpa+DMAERR),
		gsc_readl(hpa+DIOERR), gsc_readl(hpa+HIDMAMEM));
}

void pa7300lc_init(void)
{
	cpu_lpmc = pa7300lc_lpmc;
}
