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
#ifndef _POWERPC_BOOT_4XX_H_
#define _POWERPC_BOOT_4XX_H_

void ibm4xx_sdram_fixup_memsize(void);
void ibm440spe_fixup_memsize(void);
void ibm4xx_denali_fixup_memsize(void);
void ibm44x_dbcr_reset(void);
void ibm40x_dbcr_reset(void);
void ibm4xx_quiesce_eth(u32 *emac0, u32 *emac1);
void ibm4xx_fixup_ebc_ranges(const char *ebc);

void ibm405gp_fixup_clocks(unsigned int sys_clk, unsigned int ser_clk);
void ibm405ep_fixup_clocks(unsigned int sys_clk);
void ibm405ex_fixup_clocks(unsigned int sys_clk, unsigned int uart_clk);
void ibm440gp_fixup_clocks(unsigned int sys_clk, unsigned int ser_clk);
void ibm440ep_fixup_clocks(unsigned int sys_clk, unsigned int ser_clk,
			   unsigned int tmr_clk);
void ibm440gx_fixup_clocks(unsigned int sys_clk, unsigned int ser_clk,
			   unsigned int tmr_clk);
void ibm440spe_fixup_clocks(unsigned int sys_clk, unsigned int ser_clk,
			    unsigned int tmr_clk);

#endif /* _POWERPC_BOOT_4XX_H_ */
