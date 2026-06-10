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
#ifndef __SYS_SIGCONTEXT_PPC_H
#define __SYS_SIGCONTEXT_PPC_H

#define DSISR_WRITE 0x02000000

#define SC_FAULT_ADDR(sc) ({ \
		struct sigcontext *_sc = (sc); \
		long retval = -1; \
		switch (_sc->regs->trap) { \
		case 0x300: \
			/* data exception */ \
			retval = _sc->regs->dar; \
			break; \
		case 0x400: \
			/* instruction exception */ \
			retval = _sc->regs->nip; \
			break; \
		default: \
			panic("SC_FAULT_ADDR: unhandled trap type\n"); \
		} \
		retval; \
	})

#define SC_FAULT_WRITE(sc) ({ \
		struct sigcontext *_sc = (sc); \
		long retval = -1; \
		switch (_sc->regs->trap) { \
		case 0x300: \
			/* data exception */ \
			retval = !!(_sc->regs->dsisr & DSISR_WRITE); \
			break; \
		case 0x400: \
			/* instruction exception: not a write */ \
			retval = 0; \
			break; \
		default: \
			panic("SC_FAULT_ADDR: unhandled trap type\n"); \
		} \
		retval; \
	})

#define SC_IP(sc) ((sc)->regs->nip)
#define SC_SP(sc) ((sc)->regs->gpr[1])
#define SEGV_IS_FIXABLE(sc) (1)

#endif

