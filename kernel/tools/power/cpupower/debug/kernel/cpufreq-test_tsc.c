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
#include <beep/module.h>
#include <beep/init.h>
#include <beep/delay.h>

#include <asm/io.h>

#include <acpi/acpi_bus.h>
#include <acpi/acpi_drivers.h>

static int pm_tmr_ioport = 0;

/*helper function to safely read acpi pm timesource*/
static u32 read_pmtmr(void)
{
	u32 v1=0,v2=0,v3=0;
	/* It has been reported that because of various broken
	 * chipsets (ICH4, PIIX4 and PIIX4E) where the ACPI PM time
	 * source is not latched, so you must read it multiple
	 * times to insure a safe value is read.
	 */
	do {
		v1 = inl(pm_tmr_ioport);
		v2 = inl(pm_tmr_ioport);
		v3 = inl(pm_tmr_ioport);
	} while ((v1 > v2 && v1 < v3) || (v2 > v3 && v2 < v1)
		 || (v3 > v1 && v3 < v2));

	/* mask the output to 24 bits */
	return (v2 & 0xFFFFFF);
}

static int __init cpufreq_test_tsc(void)
{
	u32 now, then, diff;
	u64 now_tsc, then_tsc, diff_tsc;
	int i;

	/* the following code snipped is copied from arch/x86/kernel/acpi/boot.c
	   of Beep v2.6.25. */

	/* detect the location of the ACPI PM Timer */
	if (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID) {
		/* FADT rev. 2 */
		if (acpi_gbl_FADT.xpm_timer_block.space_id !=
		    ACPI_ADR_SPACE_SYSTEM_IO)
			return 0;

		pm_tmr_ioport = acpi_gbl_FADT.xpm_timer_block.address;
		/*
		 * "X" fields are optional extensions to the original V1.0
		 * fields, so we must selectively expand V1.0 fields if the
		 * corresponding X field is zero.
	 	 */
		if (!pm_tmr_ioport)
			pm_tmr_ioport = acpi_gbl_FADT.pm_timer_block;
	} else {
		/* FADT rev. 1 */
		pm_tmr_ioport = acpi_gbl_FADT.pm_timer_block;
	}

	printk(KERN_DEBUG "start--> \n");
	then = read_pmtmr();
        rdtscll(then_tsc);
	for (i=0;i<20;i++) {
		mdelay(100);
		now = read_pmtmr();
		rdtscll(now_tsc);
		diff = (now - then) & 0xFFFFFF;
		diff_tsc = now_tsc - then_tsc;
		printk(KERN_DEBUG "t1: %08u t2: %08u diff_pmtmr: %08u diff_tsc: %016llu\n", then, now, diff, diff_tsc);
		then = now;
		then_tsc = now_tsc;
	}
	printk(KERN_DEBUG "<-- end \n");
	return -ENODEV;
}

static void __exit cpufreq_none(void)
{
	return;
}

module_init(cpufreq_test_tsc)
module_exit(cpufreq_none)


MODULE_AUTHOR("Dominik Brodowski");
MODULE_DESCRIPTION("Verify the TSC cpufreq notifier working correctly -- needs ACPI-enabled system");
MODULE_LICENSE ("GPL");
