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
#ifndef _ASM_SGI_SGI_H
#define _ASM_SGI_SGI_H

/* UP=UniProcessor MP=MultiProcessor(capable) */
enum sgi_mach {
	ip4,	/* R2k UP */
	ip5,	/* R2k MP */
	ip6,	/* R3k UP */
	ip7,	/* R3k MP */
	ip9,	/* R3k UP */
	ip12,	/* R3kA UP, Indigo */
	ip15,	/* R3kA MP */
	ip17,	/* R4K UP */
	ip19,	/* R4K MP */
	ip20,	/* R4K UP, Indigo */
	ip21,	/* TFP MP */
	ip22,	/* R4x00 UP, Indigo2 */
	ip25,	/* R10k MP */
	ip26,	/* TFP UP, Indigo2 */
	ip27,	/* R10k MP, R12k MP, Origin */
	ip28,	/* R10k UP, Indigo2 */
	ip30,	/* Octane */
	ip32,	/* O2 */
};

extern enum sgi_mach sgimach;
extern void sgi_sysinit(void);

/* Many I/O space registers are byte sized and are contained within
 * one byte per word, specifically the MSB, this macro helps out.
 */
#ifdef __MIPSEL__
#define SGI_MSB(regaddr)   (regaddr)
#else
#define SGI_MSB(regaddr)   ((regaddr) | 0x3)
#endif

#endif /* _ASM_SGI_SGI_H */
