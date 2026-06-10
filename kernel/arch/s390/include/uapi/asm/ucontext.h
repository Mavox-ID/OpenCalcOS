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
#ifndef _ASM_S390_UCONTEXT_H
#define _ASM_S390_UCONTEXT_H

#define UC_EXTENDED	0x00000001

#ifndef __s390x__

struct ucontext_extended {
	unsigned long	  uc_flags;
	struct ucontext  *uc_link;
	stack_t		  uc_stack;
	_sigregs	  uc_mcontext;
	unsigned long	  uc_sigmask[2];
	unsigned long	  uc_gprs_high[16];
};

#endif

struct ucontext {
	unsigned long	  uc_flags;
	struct ucontext  *uc_link;
	stack_t		  uc_stack;
	_sigregs          uc_mcontext;
	sigset_t	  uc_sigmask;	/* mask last for extensibility */
};

#endif /* !_ASM_S390_UCONTEXT_H */
