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
#ifndef _ASM_NLM_XLR_H
#define _ASM_NLM_XLR_H

/* Platform UART functions */
struct uart_port;
unsigned int nlm_xlr_uart_in(struct uart_port *, int);
void nlm_xlr_uart_out(struct uart_port *, int, int);

/* SMP helpers */
void xlr_wakeup_secondary_cpus(void);

/* XLS B silicon "Rook" */
static inline unsigned int nlm_chip_is_xls_b(void)
{
	uint32_t prid = read_c0_prid();

	return ((prid & 0xf000) == 0x4000);
}

/*  XLR chip types */
/* The XLS product line has chip versions 0x[48c]? */
static inline unsigned int nlm_chip_is_xls(void)
{
	uint32_t prid = read_c0_prid();

	return ((prid & 0xf000) == 0x8000 || (prid & 0xf000) == 0x4000 ||
		(prid & 0xf000) == 0xc000);
}

#endif /* _ASM_NLM_XLR_H */
