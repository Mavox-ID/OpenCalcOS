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
#ifndef __ASM_MACH_ATH79_KERNEL_ENTRY_H
#define __ASM_MACH_ATH79_KERNEL_ENTRY_H

	/*
	 * Some bootloaders set the 'Kseg0 coherency algorithm' to
	 * 'Cacheable, noncoherent, write-through, no write allocate'
	 * and this cause performance issues. Let's go and change it to
	 * 'Cacheable, noncoherent, write-back, write allocate'
	 */
	.macro	kernel_entry_setup
	mfc0	t0, CP0_CONFIG
	li	t1, ~CONF_CM_CMASK
	and	t0, t1
	ori	t0, CONF_CM_CACHABLE_NONCOHERENT
	mtc0	t0, CP0_CONFIG
	nop
	.endm

	.macro	smp_slave_setup
	.endm

#endif /* __ASM_MACH_ATH79_KERNEL_ENTRY_H */
