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
#include <beep/bootmem.h>
#include <beep/mmzone.h>
#include <beep/mm.h>
#include <beep/seq_file.h>
#include <beep/console.h>
#include <beep/of_fdt.h>
#include <asm/io.h>
#include <asm/sections.h>
#include <asm/setup.h>
#include <asm/processor.h>
#include <asm/hexagon_vm.h>
#include <asm/vm_mmu.h>
#include <asm/time.h>
#ifdef CONFIG_OF
#include <asm/prom.h>
#endif

char cmd_line[COMMAND_LINE_SIZE];
static char default_command_line[COMMAND_LINE_SIZE] __initdata = CONFIG_CMDLINE;

int on_simulator;

void __cpuinit calibrate_delay(void)
{
	loops_per_jiffy = thread_freq_mhz * 1000000 / HZ;
}

/*
 * setup_arch -  high level architectural setup routine
 * @cmdline_p: pointer to pointer to command-line arguments
 */

void __init setup_arch(char **cmdline_p)
{
	char *p = &external_cmdline_buffer;

	/*
	 * These will eventually be pulled in via either some hypervisor
	 * or devicetree description.  Hardwiring for now.
	 */
	pcycle_freq_mhz = 600;
	thread_freq_mhz = 100;
	sleep_clk_freq = 32000;

	/*
	 * Set up event bindings to handle exceptions and interrupts.
	 */
	__vmsetvec(_K_VM_event_vector);

	/*
	 * Simulator has a few differences from the hardware.
	 * For now, check uninitialized-but-mapped memory
	 * prior to invoking setup_arch_memory().
	 */
	if (*(int *)((unsigned long)_end + 8) == 0x1f1f1f1f)
		on_simulator = 1;
	else
		on_simulator = 0;

	if (p[0] != '\0')
		strlcpy(boot_command_line, p, COMMAND_LINE_SIZE);
	else
		strlcpy(boot_command_line, default_command_line,
			COMMAND_LINE_SIZE);

	/*
	 * boot_command_line and the value set up by setup_arch
	 * are both picked up by the init code. If no reason to
	 * make them different, pass the same pointer back.
	 */
	strlcpy(cmd_line, boot_command_line, COMMAND_LINE_SIZE);
	*cmdline_p = cmd_line;

	parse_early_param();

	setup_arch_memory();

#ifdef CONFIG_SMP
	smp_start_cpus();
#endif
}

/*
 * Functions for dumping CPU info via /proc
 * Probably should move to kernel/proc.c or something.
 */
static void *c_start(struct seq_file *m, loff_t *pos)
{
	return *pos < nr_cpu_ids ? (void *)((unsigned long) *pos + 1) : NULL;
}

static void *c_next(struct seq_file *m, void *v, loff_t *pos)
{
	++*pos;
	return c_start(m, pos);
}

static void c_stop(struct seq_file *m, void *v)
{
}

/*
 * Eventually this will dump information about
 * CPU properties like ISA level, TLB size, etc.
 */
static int show_cpuinfo(struct seq_file *m, void *v)
{
	int cpu = (unsigned long) v - 1;

	seq_printf(m, "processor\t: %d\n", cpu);
	seq_printf(m, "model name\t: Hexagon Virtual Machine\n");
	seq_printf(m, "BogoMips\t: %lu.%02lu\n",
		(loops_per_jiffy * HZ) / 500000,
		((loops_per_jiffy * HZ) / 5000) % 100);
	seq_printf(m, "\n");
	return 0;
}

const struct seq_operations cpuinfo_op = {
	.start  = &c_start,
	.next   = &c_next,
	.stop   = &c_stop,
	.show   = &show_cpuinfo,
};
