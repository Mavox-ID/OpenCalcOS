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
#undef DEBUG
#include <asm/time.h>
#include <asm/prom.h>
#include <asm/machdep.h>
#include <asm/mpc52xx.h>

/*
 * Setup the architecture
 */
static void __init mpc5200_simple_setup_arch(void)
{
	if (ppc_md.progress)
		ppc_md.progress("mpc5200_simple_setup_arch()", 0);

	/* Map important registers from the internal memory map */
	mpc52xx_map_common_devices();

	/* Some mpc5200 & mpc5200b related configuration */
	mpc5200_setup_xlb_arbiter();

	mpc52xx_setup_pci();
}

/* list of the supported boards */
static const char *board[] __initdata = {
	"anonymous,a3m071",
	"anonymous,a4m072",
	"anon,charon",
	"ifm,o2d",
	"intercontrol,digsy-mtc",
	"manroland,mucmc52",
	"manroland,uc101",
	"phytec,pcm030",
	"phytec,pcm032",
	"promess,motionpro",
	"schindler,cm5200",
	"tqc,tqm5200",
	NULL
};

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
static int __init mpc5200_simple_probe(void)
{
	return of_flat_dt_match(of_get_flat_dt_root(), board);
}

define_machine(mpc5200_simple_platform) {
	.name		= "mpc5200-simple-platform",
	.probe		= mpc5200_simple_probe,
	.setup_arch	= mpc5200_simple_setup_arch,
	.init		= mpc52xx_declare_of_platform_devices,
	.init_IRQ	= mpc52xx_init_irq,
	.get_irq	= mpc52xx_get_irq,
	.restart	= mpc52xx_restart,
	.calibrate_decr	= generic_calibrate_decr,
};
