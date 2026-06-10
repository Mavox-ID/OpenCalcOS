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
#define M32R_MAX_PCC	2

/*
 * M32R PC Card Controller
 */
#define M32R_PCC0_BASE        0x00ef7000
#define M32R_PCC1_BASE        0x00ef7020

/*
 * Register offsets
 */
#define PCCR            0x00
#define PCADR           0x04
#define PCMOD           0x08
#define PCIRC           0x0c
#define PCCSIGCR        0x10
#define PCATCR          0x14

/*
 * PCCR
 */
#define PCCR_PCEN       (1UL<<(31-31))

/*
 * PCIRC
 */
#define PCIRC_BWERR     (1UL<<(31-7))
#define PCIRC_CDIN1     (1UL<<(31-14))
#define PCIRC_CDIN2     (1UL<<(31-15))
#define PCIRC_BEIEN     (1UL<<(31-23))
#define PCIRC_CIIEN     (1UL<<(31-30))
#define PCIRC_COIEN     (1UL<<(31-31))

/*
 * PCCSIGCR
 */
#define PCCSIGCR_SEN    (1UL<<(31-3))
#define PCCSIGCR_VEN    (1UL<<(31-7))
#define PCCSIGCR_CRST   (1UL<<(31-15))
#define PCCSIGCR_COCR   (1UL<<(31-31))

/*
 *
 */
#define PCMOD_AS_ATTRIB	(1UL<<(31-19))
#define PCMOD_AS_IO	(1UL<<(31-18))

#define PCMOD_CBSZ	(1UL<<(31-23)) /* set for 8bit */

#define PCMOD_DBEX	(1UL<<(31-31)) /* set for excahnge */

/*
 * M32R PCC Map addr
 */
#define M32R_PCC0_MAPBASE        0x14000000
#define M32R_PCC1_MAPBASE        0x16000000

#define M32R_PCC_MAPMAX		 0x02000000

#define M32R_PCC_MAPSIZE	 0x00001000 /* XXX */
#define M32R_PCC_MAPMASK     	(~(M32R_PCC_MAPMAX-1))
