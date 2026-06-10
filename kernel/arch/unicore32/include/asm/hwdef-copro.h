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
#ifndef __UNICORE_HWDEF_COPRO_H__
#define __UNICORE_HWDEF_COPRO_H__

/*
 * Control Register bits (CP#0 CR1)
 */
#define CR_M	(1 << 0)	/* MMU enable				*/
#define CR_A	(1 << 1)	/* Alignment abort enable		*/
#define CR_D	(1 << 2)	/* Dcache enable			*/
#define CR_I	(1 << 3)	/* Icache enable			*/
#define CR_B	(1 << 4)	/* Dcache write mechanism: write back	*/
#define CR_T	(1 << 5)	/* Burst enable				*/
#define CR_V	(1 << 13)	/* Vectors relocated to 0xffff0000	*/

#ifndef __ASSEMBLY__

#define vectors_high()		(cr_alignment & CR_V)

extern unsigned long cr_no_alignment;	/* defined in entry.S */
extern unsigned long cr_alignment;	/* defined in entry.S */

static inline unsigned int get_cr(void)
{
	unsigned int val;
	asm("movc %0, p0.c1, #0" : "=r" (val) : : "cc");
	return val;
}

static inline void set_cr(unsigned int val)
{
	asm volatile("movc p0.c1, %0, #0" : : "r" (val) : "cc");
	isb();
}

extern void adjust_cr(unsigned long mask, unsigned long set);

#endif /* __ASSEMBLY__ */

#endif /* __UNICORE_HWDEF_COPRO_H__ */
