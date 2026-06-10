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
#ifndef __ASM_ARCH_TI81XX_H
#define __ASM_ARCH_TI81XX_H

#define L4_SLOW_TI81XX_BASE	0x48000000

#define TI81XX_SCM_BASE		0x48140000
#define TI81XX_CTRL_BASE	TI81XX_SCM_BASE
#define TI81XX_PRCM_BASE	0x48180000

/*
 * Adjust TAP register base such that omap3_check_revision accesses the correct
 * TI81XX register for checking device ID (it adds 0x204 to tap base while
 * TI81XX DEVICE ID register is at offset 0x600 from control base).
 */
#define TI81XX_TAP_BASE		(TI81XX_CTRL_BASE + \
				 TI81XX_CONTROL_DEVICE_ID - 0x204)


#define TI81XX_ARM_INTC_BASE	0x48200000

#endif /* __ASM_ARCH_TI81XX_H */
