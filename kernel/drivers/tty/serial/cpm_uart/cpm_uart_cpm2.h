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
#ifndef CPM_UART_CPM2_H
#define CPM_UART_CPM2_H

#include <asm/cpm2.h>

static inline void cpm_set_brg(int brg, int baud)
{
	cpm_setbrg(brg, baud);
}

static inline void cpm_set_scc_fcr(scc_uart_t __iomem *sup)
{
	out_8(&sup->scc_genscc.scc_rfcr, CPMFCR_GBL | CPMFCR_EB);
	out_8(&sup->scc_genscc.scc_tfcr, CPMFCR_GBL | CPMFCR_EB);
}

static inline void cpm_set_smc_fcr(smc_uart_t __iomem *up)
{
	out_8(&up->smc_rfcr, CPMFCR_GBL | CPMFCR_EB);
	out_8(&up->smc_tfcr, CPMFCR_GBL | CPMFCR_EB);
}

#define DPRAM_BASE	((u8 __iomem __force *)cpm_dpram_addr(0))

#endif
