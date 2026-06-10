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
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/threads.h>

#include <asm/asm.h>
#include <asm/asm-offsets.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <asm/string.h>

#include <asm/netlogic/haldefs.h>
#include <asm/netlogic/common.h>
#include <asm/netlogic/mips-extns.h>

#include <asm/netlogic/xlp-hal/iomap.h>
#include <asm/netlogic/xlp-hal/pic.h>
#include <asm/netlogic/xlp-hal/xlp.h>
#include <asm/netlogic/xlp-hal/sys.h>

static int xlp_wakeup_core(uint64_t sysbase, int core)
{
	uint32_t coremask, value;
	int count;

	coremask = (1 << core);

	/* Enable CPU clock */
	value = nlm_read_sys_reg(sysbase, SYS_CORE_DFS_DIS_CTRL);
	value &= ~coremask;
	nlm_write_sys_reg(sysbase, SYS_CORE_DFS_DIS_CTRL, value);

	/* Remove CPU Reset */
	value = nlm_read_sys_reg(sysbase, SYS_CPU_RESET);
	value &= ~coremask;
	nlm_write_sys_reg(sysbase, SYS_CPU_RESET, value);

	/* Poll for CPU to mark itself coherent */
	count = 100000;
	do {
		value = nlm_read_sys_reg(sysbase, SYS_CPU_NONCOHERENT_MODE);
	} while ((value & coremask) != 0 && --count > 0);

	return count != 0;
}

static void xlp_enable_secondary_cores(const cpumask_t *wakeup_mask)
{
	struct nlm_soc_info *nodep;
	uint64_t syspcibase;
	uint32_t syscoremask;
	int core, n, cpu;

	for (n = 0; n < NLM_NR_NODES; n++) {
		syspcibase = nlm_get_sys_pcibase(n);
		if (nlm_read_reg(syspcibase, 0) == 0xffffffff)
			break;

		/* read cores in reset from SYS and account for boot cpu */
		nlm_node_init(n);
		nodep = nlm_get_node(n);
		syscoremask = nlm_read_sys_reg(nodep->sysbase, SYS_CPU_RESET);
		if (n == 0)
			syscoremask |= 1;

		for (core = 0; core < NLM_CORES_PER_NODE; core++) {
			/* see if the core exists */
			if ((syscoremask & (1 << core)) == 0)
				continue;

			/* see if at least the first thread is enabled */
			cpu = (n * NLM_CORES_PER_NODE + core)
						* NLM_THREADS_PER_CORE;
			if (!cpumask_test_cpu(cpu, wakeup_mask))
				continue;

			/* wake up the core */
			if (xlp_wakeup_core(nodep->sysbase, core))
				nodep->coremask |= 1u << core;
			else
				pr_err("Failed to enable core %d\n", core);
		}
	}
}

void xlp_wakeup_secondary_cpus()
{
	/*
	 * In case of u-boot, the secondaries are in reset
	 * first wakeup core 0 threads
	 */
	xlp_boot_core0_siblings();

	/* now get other cores out of reset */
	xlp_enable_secondary_cores(&nlm_cpumask);
}
