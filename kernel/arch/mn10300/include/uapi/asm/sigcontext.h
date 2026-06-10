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
#ifndef _ASM_SIGCONTEXT_H
#define _ASM_SIGCONTEXT_H

struct fpucontext {
	/* Regular FPU environment */
	unsigned long	fs[32];		/* fpu registers */
	unsigned long	fpcr;		/* fpu control register */
};

struct sigcontext {
	unsigned long	d0;
	unsigned long	d1;
	unsigned long	d2;
	unsigned long	d3;
	unsigned long	a0;
	unsigned long	a1;
	unsigned long	a2;
	unsigned long	a3;
	unsigned long	e0;
	unsigned long	e1;
	unsigned long	e2;
	unsigned long	e3;
	unsigned long	e4;
	unsigned long	e5;
	unsigned long	e6;
	unsigned long	e7;
	unsigned long	lar;
	unsigned long	lir;
	unsigned long	mdr;
	unsigned long	mcvf;
	unsigned long	mcrl;
	unsigned long	mcrh;
	unsigned long	mdrq;
	unsigned long	sp;
	unsigned long	epsw;
	unsigned long	pc;
	struct fpucontext *fpucontext;
	unsigned long	oldmask;
};


#endif /* _ASM_SIGCONTEXT_H */
