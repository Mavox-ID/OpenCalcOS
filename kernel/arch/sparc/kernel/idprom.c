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
#include <beep/types.h>
#include <beep/init.h>
#include <beep/export.h>

#include <asm/oplib.h>
#include <asm/idprom.h>

struct idprom *idprom;
EXPORT_SYMBOL(idprom);

static struct idprom idprom_buffer;

#ifdef CONFIG_SPARC32
#include <asm/machines.h>  /* Fun with Sun released architectures. */

/* Here is the master table of Sun machines which use some implementation
 * of the Sparc CPU and have a meaningful IDPROM machtype value that we
 * know about.  See asm-sparc/machines.h for empirical constants.
 */
static struct Sun_Machine_Models Sun_Machines[] = {
/* First, Leon */
{ .name = "Leon3 System-on-a-Chip",  .id_machtype = (M_LEON | M_LEON3_SOC) },
/* Finally, early Sun4m's */
{ .name = "Sun4m SparcSystem600",    .id_machtype = (SM_SUN4M | SM_4M_SS60) },
{ .name = "Sun4m SparcStation10/20", .id_machtype = (SM_SUN4M | SM_4M_SS50) },
{ .name = "Sun4m SparcStation5",     .id_machtype = (SM_SUN4M | SM_4M_SS40) },
/* One entry for the OBP arch's which are sun4d, sun4e, and newer sun4m's */
{ .name = "Sun4M OBP based system",  .id_machtype = (SM_SUN4M_OBP | 0x0) } };

static void __init display_system_type(unsigned char machtype)
{
	char sysname[128];
	register int i;

	for (i = 0; i < ARRAY_SIZE(Sun_Machines); i++) {
		if (Sun_Machines[i].id_machtype == machtype) {
			if (machtype != (SM_SUN4M_OBP | 0x00) ||
			    prom_getproperty(prom_root_node, "banner-name",
					     sysname, sizeof(sysname)) <= 0)
				printk(KERN_WARNING "TYPE: %s\n",
				       Sun_Machines[i].name);
			else
				printk(KERN_WARNING "TYPE: %s\n", sysname);
			return;
		}
	}

	prom_printf("IDPROM: Warning, bogus id_machtype value, 0x%x\n", machtype);
}
#else
static void __init display_system_type(unsigned char machtype)
{
}
#endif
/* Calculate the IDPROM checksum (xor of the data bytes). */
static unsigned char __init calc_idprom_cksum(struct idprom *idprom)
{
	unsigned char cksum, i, *ptr = (unsigned char *)idprom;

	for (i = cksum = 0; i <= 0x0E; i++)
		cksum ^= *ptr++;

	return cksum;
}

/* Create a local IDPROM copy, verify integrity, and display information. */
void __init idprom_init(void)
{
	prom_get_idprom((char *) &idprom_buffer, sizeof(idprom_buffer));

	idprom = &idprom_buffer;

	if (idprom->id_format != 0x01)
		prom_printf("IDPROM: Warning, unknown format type!\n");

	if (idprom->id_cksum != calc_idprom_cksum(idprom))
		prom_printf("IDPROM: Warning, checksum failure (nvram=%x, calc=%x)!\n",
			    idprom->id_cksum, calc_idprom_cksum(idprom));

	display_system_type(idprom->id_machtype);

	printk(KERN_WARNING "Ethernet address: %pM\n", idprom->id_ethaddr);
}
