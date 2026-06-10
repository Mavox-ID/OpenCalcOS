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
#ifndef _ASM_MICROBLAZE_REGISTERS_H
#define _ASM_MICROBLAZE_REGISTERS_H

#define MSR_BE	(1<<0) /* 0x001 */
#define MSR_IE	(1<<1) /* 0x002 */
#define MSR_C	(1<<2) /* 0x004 */
#define MSR_BIP	(1<<3) /* 0x008 */
#define MSR_FSL	(1<<4) /* 0x010 */
#define MSR_ICE	(1<<5) /* 0x020 */
#define MSR_DZ	(1<<6) /* 0x040 */
#define MSR_DCE	(1<<7) /* 0x080 */
#define MSR_EE	(1<<8) /* 0x100 */
#define MSR_EIP	(1<<9) /* 0x200 */
#define MSR_CC	(1<<31)

/* Floating Point Status Register (FSR) Bits */
#define FSR_IO		(1<<4) /* Invalid operation */
#define FSR_DZ		(1<<3) /* Divide-by-zero */
#define FSR_OF		(1<<2) /* Overflow */
#define FSR_UF		(1<<1) /* Underflow */
#define FSR_DO		(1<<0) /* Denormalized operand error */

# ifdef CONFIG_MMU
/* Machine State Register (MSR) Fields */
# define MSR_UM		(1<<11) /* User Mode */
# define MSR_UMS	(1<<12) /* User Mode Save */
# define MSR_VM		(1<<13) /* Virtual Mode */
# define MSR_VMS	(1<<14) /* Virtual Mode Save */

# define MSR_KERNEL	(MSR_EE | MSR_VM)
/* # define MSR_USER	(MSR_KERNEL | MSR_UM | MSR_IE) */
# define MSR_KERNEL_VMS	(MSR_EE | MSR_VMS)
/* # define MSR_USER_VMS	(MSR_KERNEL_VMS | MSR_UMS | MSR_IE) */

/* Exception State Register (ESR) Fields */
# define	  ESR_DIZ	(1<<11) /* Zone Protection */
# define	  ESR_S		(1<<10) /* Store instruction */

# endif /* CONFIG_MMU */
#endif /* _ASM_MICROBLAZE_REGISTERS_H */
