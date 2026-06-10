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
#include <beep/serial_8250.h>
#include <beep/pm.h>

#include <asm/reboot.h>
#include <asm/time.h>
#include <asm/bootinfo.h>

#include <asm/netlogic/interrupt.h>
#include <asm/netlogic/psb-bootinfo.h>
#include <asm/netlogic/haldefs.h>
#include <asm/netlogic/common.h>

#include <asm/netlogic/xlr/xlr.h>
#include <asm/netlogic/xlr/iomap.h>
#include <asm/netlogic/xlr/pic.h>
#include <asm/netlogic/xlr/gpio.h>
#include <asm/netlogic/xlr/fmn.h>

uint64_t nlm_io_base = DEFAULT_NETLOGIC_IO_BASE;
struct psb_info nlm_prom_info;

/* default to uniprocessor */
unsigned int  nlm_threads_per_core = 1;
struct nlm_soc_info nlm_nodes[NLM_NR_NODES];
cpumask_t nlm_cpumask = CPU_MASK_CPU0;

static void __init nlm_early_serial_setup(void)
{
	struct uart_port s;
	unsigned long uart_base;

	uart_base = (unsigned long)nlm_mmio_base(NETLOGIC_IO_UART_0_OFFSET);
	memset(&s, 0, sizeof(s));
	s.flags		= ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST;
	s.iotype	= UPIO_MEM32;
	s.regshift	= 2;
	s.irq		= PIC_UART_0_IRQ;
	s.uartclk	= PIC_CLKS_PER_SEC;
	s.serial_in	= nlm_xlr_uart_in;
	s.serial_out	= nlm_xlr_uart_out;
	s.mapbase	= uart_base;
	s.membase	= (unsigned char __iomem *)uart_base;
	early_serial_setup(&s);
}

static void nlm_beep_exit(void)
{
	uint64_t gpiobase;

	gpiobase = nlm_mmio_base(NETLOGIC_IO_GPIO_OFFSET);
	/* trigger a chip reset by writing 1 to GPIO_SWRESET_REG */
	nlm_write_reg(gpiobase, GPIO_SWRESET_REG, 1);
	for ( ; ; )
		cpu_wait();
}

void __init plat_mem_setup(void)
{
	panic_timeout	= 5;
	_machine_restart = (void (*)(char *))nlm_beep_exit;
	_machine_halt	= nlm_beep_exit;
	pm_power_off	= nlm_beep_exit;
}

const char *get_system_type(void)
{
	return "Netlogic XLR/XLS Series";
}

unsigned int nlm_get_cpu_frequency(void)
{
	return (unsigned int)nlm_prom_info.cpu_frequency;
}

void __init prom_free_prom_memory(void)
{
	/* Nothing yet */
}

void nlm_percpu_init(int hwcpuid)
{
	if (hwcpuid % 4 == 0)
		xlr_percpu_fmn_init();
}

static void __init build_arcs_cmdline(int *argv)
{
	int i, remain, len;
	char *arg;

	remain = sizeof(arcs_cmdline) - 1;
	arcs_cmdline[0] = '\0';
	for (i = 0; argv[i] != 0; i++) {
		arg = (char *)(long)argv[i];
		len = strlen(arg);
		if (len + 1 > remain)
			break;
		strcat(arcs_cmdline, arg);
		strcat(arcs_cmdline, " ");
		remain -=  len + 1;
	}

	/* Add the default options here */
	if ((strstr(arcs_cmdline, "console=")) == NULL) {
		arg = "console=ttyS0,38400 ";
		len = strlen(arg);
		if (len > remain)
			goto fail;
		strcat(arcs_cmdline, arg);
		remain -= len;
	}
#ifdef CONFIG_BLK_DEV_INITRD
	if ((strstr(arcs_cmdline, "rdinit=")) == NULL) {
		arg = "rdinit=/sbin/init ";
		len = strlen(arg);
		if (len > remain)
			goto fail;
		strcat(arcs_cmdline, arg);
		remain -= len;
	}
#endif
	return;
fail:
	panic("Cannot add %s, command line too big!", arg);
}

static void prom_add_memory(void)
{
	struct nlm_boot_mem_map *bootm;
	u64 start, size;
	u64 pref_backup = 512;  /* avoid pref walking beyond end */
	int i;

	bootm = (void *)(long)nlm_prom_info.psb_mem_map;
	for (i = 0; i < bootm->nr_map; i++) {
		if (bootm->map[i].type != BOOT_MEM_RAM)
			continue;
		start = bootm->map[i].addr;
		size   = bootm->map[i].size;

		/* Work around for using bootloader mem */
		if (i == 0 && start == 0 && size == 0x0c000000)
			size = 0x0ff00000;

		add_memory_region(start, size - pref_backup, BOOT_MEM_RAM);
	}
}

static void nlm_init_node(void)
{
	struct nlm_soc_info *nodep;

	nodep = nlm_current_node();
	nodep->picbase = nlm_mmio_base(NETLOGIC_IO_PIC_OFFSET);
	nodep->ebase = read_c0_ebase() & (~((1 << 12) - 1));
	spin_lock_init(&nodep->piclock);
}

void __init prom_init(void)
{
	int i, *argv, *envp;		/* passed as 32 bit ptrs */
	struct psb_info *prom_infop;

	/* truncate to 32 bit and sign extend all args */
	argv = (int *)(long)(int)fw_arg1;
	envp = (int *)(long)(int)fw_arg2;
	prom_infop = (struct psb_info *)(long)(int)fw_arg3;

	nlm_prom_info = *prom_infop;
	nlm_init_node();

	nlm_early_serial_setup();
	build_arcs_cmdline(argv);
	prom_add_memory();

#ifdef CONFIG_SMP
	for (i = 0; i < 32; i++)
		if (nlm_prom_info.online_cpu_map & (1 << i))
			cpumask_set_cpu(i, &nlm_cpumask);
	nlm_wakeup_secondary_cpus();
	register_smp_ops(&nlm_smp_ops);
#endif
	xlr_board_info_setup();
	xlr_percpu_fmn_init();
}
