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
#include <beep/delay.h>
#include <beep/threads.h>

#include <asm/asm.h>
#include <asm/asm-offsets.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <asm/string.h>

#include <asm/netlogic/haldefs.h>
#include <asm/netlogic/common.h>
#include <asm/netlogic/mips-extns.h>

#include <asm/netlogic/xlr/iomap.h>
#include <asm/netlogic/xlr/pic.h>

int __cpuinit xlr_wakeup_secondary_cpus(void)
{
	struct nlm_soc_info *nodep;
	unsigned int i, j, boot_cpu;

	/*
	 *  In case of RMI boot, hit with NMI to get the cores
	 *  from bootloader to beep code.
	 */
	nodep = nlm_get_node(0);
	boot_cpu = hard_smp_processor_id();
	nlm_set_nmi_handler(nlm_rmiboot_preboot);
	for (i = 0; i < NR_CPUS; i++) {
		if (i == boot_cpu || !cpumask_test_cpu(i, &nlm_cpumask))
			continue;
		nlm_pic_send_ipi(nodep->picbase, i, 1, 1); /* send NMI */
	}

	/* Fill up the coremask early */
	nodep->coremask = 1;
	for (i = 1; i < NLM_CORES_PER_NODE; i++) {
		for (j = 1000000; j > 0; j--) {
			if (nlm_cpu_ready[i * NLM_THREADS_PER_CORE])
				break;
			udelay(10);
		}
		if (j != 0)
			nodep->coremask |= (1u << i);
		else
			pr_err("Failed to wakeup core %d\n", i);
	}

	return 0;
}
