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
#ifndef __ASM_ARCH_OSIRISCPLD_H
#define __ASM_ARCH_OSIRISCPLD_H

/* CTRL0 - NAND WP control */

#define OSIRIS_CTRL0_NANDSEL		(0x3)
#define OSIRIS_CTRL0_BOOT_INT		(1<<3)
#define OSIRIS_CTRL0_PCMCIA		(1<<4)
#define OSIRIS_CTRL0_FIX8		(1<<5)
#define OSIRIS_CTRL0_PCMCIA_nWAIT	(1<<6)
#define OSIRIS_CTRL0_PCMCIA_nIOIS16	(1<<7)

#define OSIRIS_CTRL1_FIX8		(1<<0)

#define OSIRIS_ID_REVMASK		(0x7)

#endif /* __ASM_ARCH_OSIRISCPLD_H */
