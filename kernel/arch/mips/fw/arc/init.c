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

#include <asm/bootinfo.h>
#include <asm/sgialib.h>
#include <asm/smp-ops.h>

#undef DEBUG_PROM_INIT

/* Master romvec interface. */
struct beep_romvec *romvec;
int prom_argc;
LONG *_prom_argv, *_prom_envp;

void __init prom_init(void)
{
	PSYSTEM_PARAMETER_BLOCK pb = PROMBLOCK;

	romvec = ROMVECTOR;

	prom_argc = fw_arg0;
	_prom_argv = (LONG *) fw_arg1;
	_prom_envp = (LONG *) fw_arg2;

	if (pb->magic != 0x53435241) {
		printk(KERN_CRIT "Aieee, bad prom vector magic %08lx\n",
		       (unsigned long) pb->magic);
		while(1)
			;
	}

	prom_init_cmdline();
	prom_identify_arch();
	printk(KERN_INFO "PROMLIB: ARC firmware Version %d Revision %d\n",
	       pb->ver, pb->rev);
	prom_meminit();

#ifdef DEBUG_PROM_INIT
	pr_info("Press a key to reboot\n");
	ArcRead(0, &c, 1, &cnt);
	ArcEnterInteractiveMode();
#endif
#ifdef CONFIG_SGI_IP27
	{
		extern struct plat_smp_ops ip27_smp_ops;

		register_smp_ops(&ip27_smp_ops);
	}
#endif
}
