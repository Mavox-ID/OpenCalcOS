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
#ifndef _SPARC_MACHINES_H
#define _SPARC_MACHINES_H

struct Sun_Machine_Models {
	char *name;
	unsigned char id_machtype;
};

/* The machine type in the idprom area looks like this:
 *
 * ---------------
 * | ARCH | MACH |
 * ---------------
 *  7    4 3    0
 *
 * The ARCH field determines the architecture line (sun4m, etc).
 * The MACH field determines the machine make within that architecture.
 */

#define SM_ARCH_MASK  0xf0
#define  M_LEON       0x30
#define SM_SUN4M      0x70
#define SM_SUN4M_OBP  0x80

#define SM_TYP_MASK   0x0f

/* Leon machines */
#define M_LEON3_SOC   0x02    /* Leon3 SoC */

/* Sun4m machines, these predate the OpenBoot.  These values only mean
 * something if the value in the ARCH field is SM_SUN4M, if it is
 * SM_SUN4M_OBP then you have the following situation:
 * 1) You either have a sun4d, a sun4e, or a recently made sun4m.
 * 2) You have to consult OpenBoot to determine which machine this is.
 */
#define SM_4M_SS60    0x01    /* Sun4m SparcSystem 600                  */
#define SM_4M_SS50    0x02    /* Sun4m SparcStation 10                  */
#define SM_4M_SS40    0x03    /* Sun4m SparcStation 5                   */

/* Sun4d machines -- N/A */
/* Sun4e machines -- N/A */
/* Sun4u machines -- N/A */

#endif /* !(_SPARC_MACHINES_H) */
