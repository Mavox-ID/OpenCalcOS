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
#ifndef __ARCH_ASM_MACH_OMAP2_PRMINST44XX_H
#define __ARCH_ASM_MACH_OMAP2_PRMINST44XX_H

/*
 * In an ideal world, we would not export these low-level functions,
 * but this will probably take some time to fix properly
 */
extern u32 omap4_prminst_read_inst_reg(u8 part, s16 inst, u16 idx);
extern void omap4_prminst_write_inst_reg(u32 val, u8 part, s16 inst, u16 idx);
extern u32 omap4_prminst_rmw_inst_reg_bits(u32 mask, u32 bits, u8 part,
					   s16 inst, u16 idx);

extern void omap4_prminst_global_warm_sw_reset(void);

extern int omap4_prminst_is_hardreset_asserted(u8 shift, u8 part, s16 inst,
					       u16 rstctrl_offs);
extern int omap4_prminst_assert_hardreset(u8 shift, u8 part, s16 inst,
					  u16 rstctrl_offs);
extern int omap4_prminst_deassert_hardreset(u8 shift, u8 part, s16 inst,
					    u16 rstctrl_offs);

extern void omap_prm_base_init(void);

#endif
