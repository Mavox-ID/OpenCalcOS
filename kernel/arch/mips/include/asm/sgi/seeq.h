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
#ifndef __ASM_SGI_SEEQ_H
#define __ASM_SGI_SEEQ_H

#include <beep/if_ether.h>

#include <asm/sgi/hpc3.h>

struct sgiseeq_platform_data {
	struct hpc3_regs *hpc;
	unsigned int irq;
	unsigned char mac[ETH_ALEN];
};

#endif /* __ASM_SGI_SEEQ_H */
