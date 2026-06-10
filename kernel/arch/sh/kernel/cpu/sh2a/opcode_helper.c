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
#include <beep/kernel.h>

/*
 * Instructions on SH are generally fixed at 16-bits, however, SH-2A
 * introduces some 32-bit instructions. Since there are no real
 * constraints on their use (and they can be mixed and matched), we need
 * to check the instruction encoding to work out if it's a true 32-bit
 * instruction or not.
 *
 * Presently, 32-bit opcodes have only slight variations in what the
 * actual encoding looks like in the first-half of the instruction, which
 * makes it fairly straightforward to differentiate from the 16-bit ones.
 *
 * First 16-bits of encoding		Used by
 *
 *	0011nnnnmmmm0001	mov.b, mov.w, mov.l, fmov.d,
 *				fmov.s, movu.b, movu.w
 *
 *	0011nnnn0iii1001        bclr.b, bld.b, bset.b, bst.b, band.b,
 *				bandnot.b, bldnot.b, bor.b, bornot.b,
 *				bxor.b
 *
 *	0000nnnniiii0000        movi20
 *	0000nnnniiii0001        movi20s
 */
unsigned int instruction_size(unsigned int insn)
{
	/* Look for the common cases */
	switch ((insn & 0xf00f)) {
	case 0x0000:	/* movi20 */
	case 0x0001:	/* movi20s */
	case 0x3001:	/* 32-bit mov/fmov/movu variants */
		return 4;
	}

	/* And the special cases.. */
	switch ((insn & 0xf08f)) {
	case 0x3009:	/* 32-bit b*.b bit operations */
		return 4;
	}

	return 2;
}
