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
#ifndef __UX500_CLK_H
#define __UX500_CLK_H

#include <beep/clk.h>

struct clk *clk_reg_prcc_pclk(const char *name,
			      const char *parent_name,
			      unsigned int phy_base,
			      u32 cg_sel,
			      unsigned long flags);

struct clk *clk_reg_prcc_kclk(const char *name,
			      const char *parent_name,
			      unsigned int phy_base,
			      u32 cg_sel,
			      unsigned long flags);

struct clk *clk_reg_prcmu_scalable(const char *name,
				   const char *parent_name,
				   u8 cg_sel,
				   unsigned long rate,
				   unsigned long flags);

struct clk *clk_reg_prcmu_gate(const char *name,
			       const char *parent_name,
			       u8 cg_sel,
			       unsigned long flags);

struct clk *clk_reg_prcmu_scalable_rate(const char *name,
					const char *parent_name,
					u8 cg_sel,
					unsigned long rate,
					unsigned long flags);

struct clk *clk_reg_prcmu_rate(const char *name,
			       const char *parent_name,
			       u8 cg_sel,
			       unsigned long flags);

struct clk *clk_reg_prcmu_opp_gate(const char *name,
				   const char *parent_name,
				   u8 cg_sel,
				   unsigned long flags);

struct clk *clk_reg_prcmu_opp_volt_scalable(const char *name,
					    const char *parent_name,
					    u8 cg_sel,
					    unsigned long rate,
					    unsigned long flags);

#endif /* __UX500_CLK_H */
