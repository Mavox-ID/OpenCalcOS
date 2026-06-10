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
#ifndef _ASM_C6X_SIGCONTEXT_H
#define _ASM_C6X_SIGCONTEXT_H


struct sigcontext {
	unsigned long  sc_mask;		/* old sigmask */
	unsigned long  sc_sp;		/* old user stack pointer */

	unsigned long  sc_a4;
	unsigned long  sc_b4;
	unsigned long  sc_a6;
	unsigned long  sc_b6;
	unsigned long  sc_a8;
	unsigned long  sc_b8;

	unsigned long  sc_a0;
	unsigned long  sc_a1;
	unsigned long  sc_a2;
	unsigned long  sc_a3;
	unsigned long  sc_a5;
	unsigned long  sc_a7;
	unsigned long  sc_a9;

	unsigned long  sc_b0;
	unsigned long  sc_b1;
	unsigned long  sc_b2;
	unsigned long  sc_b3;
	unsigned long  sc_b5;
	unsigned long  sc_b7;
	unsigned long  sc_b9;

	unsigned long  sc_a16;
	unsigned long  sc_a17;
	unsigned long  sc_a18;
	unsigned long  sc_a19;
	unsigned long  sc_a20;
	unsigned long  sc_a21;
	unsigned long  sc_a22;
	unsigned long  sc_a23;
	unsigned long  sc_a24;
	unsigned long  sc_a25;
	unsigned long  sc_a26;
	unsigned long  sc_a27;
	unsigned long  sc_a28;
	unsigned long  sc_a29;
	unsigned long  sc_a30;
	unsigned long  sc_a31;

	unsigned long  sc_b16;
	unsigned long  sc_b17;
	unsigned long  sc_b18;
	unsigned long  sc_b19;
	unsigned long  sc_b20;
	unsigned long  sc_b21;
	unsigned long  sc_b22;
	unsigned long  sc_b23;
	unsigned long  sc_b24;
	unsigned long  sc_b25;
	unsigned long  sc_b26;
	unsigned long  sc_b27;
	unsigned long  sc_b28;
	unsigned long  sc_b29;
	unsigned long  sc_b30;
	unsigned long  sc_b31;

	unsigned long  sc_csr;
	unsigned long  sc_pc;
};

#endif /* _ASM_C6X_SIGCONTEXT_H */
