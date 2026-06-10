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
#ifndef __UNICORE_HWCAP_H__
#define __UNICORE_HWCAP_H__

/*
 * HWCAP flags
 */
#define HWCAP_MSP		1
#define HWCAP_UNICORE16		2
#define HWCAP_CMOV		4
#define HWCAP_UNICORE_F64       8
#define HWCAP_TLS		0x80

#if defined(__KERNEL__) && !defined(__ASSEMBLY__)
/*
 * This yields a mask that user programs can use to figure out what
 * instruction set this cpu supports.
 */
#define ELF_HWCAP		(HWCAP_CMOV | HWCAP_UNICORE_F64)
#endif

#endif
