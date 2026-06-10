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
#ifndef _XTENSA_SIGCONTEXT_H
#define _XTENSA_SIGCONTEXT_H


struct sigcontext {
	unsigned long sc_pc;
	unsigned long sc_ps;
	unsigned long sc_lbeg;
	unsigned long sc_lend;
	unsigned long sc_lcount;
	unsigned long sc_sar;
	unsigned long sc_acclo;
	unsigned long sc_acchi;
	unsigned long sc_a[16];
	void *sc_xtregs;
};

#endif /* _XTENSA_SIGCONTEXT_H */
