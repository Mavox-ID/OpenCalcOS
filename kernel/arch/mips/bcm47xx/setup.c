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
#include <beep/export.h>
#include <beep/types.h>
#include <beep/ssb/ssb.h>
#include <beep/ssb/ssb_embedded.h>
#include <beep/bcma/bcma_soc.h>
#include <asm/bootinfo.h>
#include <asm/reboot.h>
#include <asm/time.h>
#include <bcm47xx.h>
#include <asm/mach-bcm47xx/nvram.h>

union bcm47xx_bus bcm47xx_bus;
EXPORT_SYMBOL(bcm47xx_bus);

enum bcm47xx_bus_type bcm47xx_bus_type;
EXPORT_SYMBOL(bcm47xx_bus_type);

static void bcm47xx_machine_restart(char *command)
{
	printk(KERN_ALERT "Please stand by while rebooting the system...\n");
	local_irq_disable();
	/* Set the watchdog timer to reset immediately */
	switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		ssb_watchdog_timer_set(&bcm47xx_bus.ssb, 1);
		break;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		bcma_chipco_watchdog_timer_set(&bcm47xx_bus.bcma.bus.drv_cc, 1);
		break;
#endif
	}
	while (1)
		cpu_relax();
}

static void bcm47xx_machine_halt(void)
{
	/* Disable interrupts and watchdog and spin forever */
	local_irq_disable();
	switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		ssb_watchdog_timer_set(&bcm47xx_bus.ssb, 0);
		break;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		bcma_chipco_watchdog_timer_set(&bcm47xx_bus.bcma.bus.drv_cc, 0);
		break;
#endif
	}
	while (1)
		cpu_relax();
}

#ifdef CONFIG_BCM47XX_SSB
static int bcm47xx_get_sprom_ssb(struct ssb_bus *bus, struct ssb_sprom *out)
{
	char prefix[10];

	if (bus->bustype == SSB_BUSTYPE_PCI) {
		memset(out, 0, sizeof(struct ssb_sprom));
		snprintf(prefix, sizeof(prefix), "pci/%u/%u/",
			 bus->host_pci->bus->number + 1,
			 PCI_SLOT(bus->host_pci->devfn));
		bcm47xx_fill_sprom(out, prefix, false);
		return 0;
	} else {
		printk(KERN_WARNING "bcm47xx: unable to fill SPROM for given bustype.\n");
		return -EINVAL;
	}
}

static int bcm47xx_get_invariants(struct ssb_bus *bus,
				  struct ssb_init_invariants *iv)
{
	char buf[20];

	/* Fill boardinfo structure */
	memset(&(iv->boardinfo), 0 , sizeof(struct ssb_boardinfo));

	bcm47xx_fill_ssb_boardinfo(&iv->boardinfo, NULL);

	memset(&iv->sprom, 0, sizeof(struct ssb_sprom));
	bcm47xx_fill_sprom(&iv->sprom, NULL, false);

	if (nvram_getenv("cardbus", buf, sizeof(buf)) >= 0)
		iv->has_cardbus_slot = !!simple_strtoul(buf, NULL, 10);

	return 0;
}

static void __init bcm47xx_register_ssb(void)
{
	int err;
	char buf[100];
	struct ssb_mipscore *mcore;

	err = ssb_arch_register_fallback_sprom(&bcm47xx_get_sprom_ssb);
	if (err)
		printk(KERN_WARNING "bcm47xx: someone else already registered"
			" a ssb SPROM callback handler (err %d)\n", err);

	err = ssb_bus_ssbbus_register(&(bcm47xx_bus.ssb), SSB_ENUM_BASE,
				      bcm47xx_get_invariants);
	if (err)
		panic("Failed to initialize SSB bus (err %d)", err);

	mcore = &bcm47xx_bus.ssb.mipscore;
	if (nvram_getenv("kernel_args", buf, sizeof(buf)) >= 0) {
		if (strstr(buf, "console=ttyS1")) {
			struct ssb_serial_port port;

			printk(KERN_DEBUG "Swapping serial ports!\n");
			/* swap serial ports */
			memcpy(&port, &mcore->serial_ports[0], sizeof(port));
			memcpy(&mcore->serial_ports[0], &mcore->serial_ports[1],
			       sizeof(port));
			memcpy(&mcore->serial_ports[1], &port, sizeof(port));
		}
	}
}
#endif

#ifdef CONFIG_BCM47XX_BCMA
static int bcm47xx_get_sprom_bcma(struct bcma_bus *bus, struct ssb_sprom *out)
{
	char prefix[10];
	struct bcma_device *core;

	switch (bus->hosttype) {
	case BCMA_HOSTTYPE_PCI:
		memset(out, 0, sizeof(struct ssb_sprom));
		snprintf(prefix, sizeof(prefix), "pci/%u/%u/",
			 bus->host_pci->bus->number + 1,
			 PCI_SLOT(bus->host_pci->devfn));
		bcm47xx_fill_sprom(out, prefix, false);
		return 0;
	case BCMA_HOSTTYPE_SOC:
		memset(out, 0, sizeof(struct ssb_sprom));
		core = bcma_find_core(bus, BCMA_CORE_80211);
		if (core) {
			snprintf(prefix, sizeof(prefix), "sb/%u/",
				 core->core_index);
			bcm47xx_fill_sprom(out, prefix, true);
		} else {
			bcm47xx_fill_sprom(out, NULL, false);
		}
		return 0;
	default:
		pr_warn("bcm47xx: unable to fill SPROM for given bustype.\n");
		return -EINVAL;
	}
}

static void __init bcm47xx_register_bcma(void)
{
	int err;

	err = bcma_arch_register_fallback_sprom(&bcm47xx_get_sprom_bcma);
	if (err)
		pr_warn("bcm47xx: someone else already registered a bcma SPROM callback handler (err %d)\n", err);

	err = bcma_host_soc_register(&bcm47xx_bus.bcma);
	if (err)
		panic("Failed to initialize BCMA bus (err %d)", err);

	bcm47xx_fill_bcma_boardinfo(&bcm47xx_bus.bcma.bus.boardinfo, NULL);
}
#endif

void __init plat_mem_setup(void)
{
	struct cpuinfo_mips *c = &current_cpu_data;

	if (c->cputype == CPU_74K) {
		printk(KERN_INFO "bcm47xx: using bcma bus\n");
#ifdef CONFIG_BCM47XX_BCMA
		bcm47xx_bus_type = BCM47XX_BUS_TYPE_BCMA;
		bcm47xx_register_bcma();
#endif
	} else {
		printk(KERN_INFO "bcm47xx: using ssb bus\n");
#ifdef CONFIG_BCM47XX_SSB
		bcm47xx_bus_type = BCM47XX_BUS_TYPE_SSB;
		bcm47xx_register_ssb();
#endif
	}

	_machine_restart = bcm47xx_machine_restart;
	_machine_halt = bcm47xx_machine_halt;
	pm_power_off = bcm47xx_machine_halt;
}

static int __init bcm47xx_register_bus_complete(void)
{
	switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		/* Nothing to do */
		break;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		bcma_bus_register(&bcm47xx_bus.bcma.bus);
		break;
#endif
	}
	return 0;
}
device_initcall(bcm47xx_register_bus_complete);
