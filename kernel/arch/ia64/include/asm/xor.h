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
extern void xor_ia64_2(unsigned long, unsigned long *, unsigned long *);
extern void xor_ia64_3(unsigned long, unsigned long *, unsigned long *,
		       unsigned long *);
extern void xor_ia64_4(unsigned long, unsigned long *, unsigned long *,
		       unsigned long *, unsigned long *);
extern void xor_ia64_5(unsigned long, unsigned long *, unsigned long *,
		       unsigned long *, unsigned long *, unsigned long *);

static struct xor_block_template xor_block_ia64 = {
	.name =	"ia64",
	.do_2 =	xor_ia64_2,
	.do_3 =	xor_ia64_3,
	.do_4 =	xor_ia64_4,
	.do_5 =	xor_ia64_5,
};

#define XOR_TRY_TEMPLATES	xor_speed(&xor_block_ia64)
