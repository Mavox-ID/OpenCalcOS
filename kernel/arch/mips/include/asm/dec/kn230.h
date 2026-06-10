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
#ifndef __ASM_MIPS_DEC_KN230_H
#define __ASM_MIPS_DEC_KN230_H

/*
 * CPU interrupt bits.
 */
#define KN230_CPU_INR_HALT	6	/* HALT button */
#define KN230_CPU_INR_BUS	5	/* memory, I/O bus read/write errors */
#define KN230_CPU_INR_RTC	4	/* DS1287 RTC */
#define KN230_CPU_INR_SII	3	/* SII (DC7061) SCSI */
#define KN230_CPU_INR_LANCE	3	/* LANCE (Am7990) Ethernet */
#define KN230_CPU_INR_DZ11	2	/* DZ11 (DC7085) serial */

#endif /* __ASM_MIPS_DEC_KN230_H */
