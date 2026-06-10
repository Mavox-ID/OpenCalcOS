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
#ifndef _PCH_GBE_PHY_H_
#define _PCH_GBE_PHY_H_

#define PCH_GBE_PHY_REGS_LEN		32
#define	PCH_GBE_PHY_RESET_DELAY_US	10
#define PCH_GBE_MAC_IFOP_RGMII

s32 pch_gbe_phy_get_id(struct pch_gbe_hw *hw);
s32 pch_gbe_phy_read_reg_miic(struct pch_gbe_hw *hw, u32 offset, u16 *data);
s32 pch_gbe_phy_write_reg_miic(struct pch_gbe_hw *hw, u32 offset, u16 data);
void pch_gbe_phy_sw_reset(struct pch_gbe_hw *hw);
void pch_gbe_phy_hw_reset(struct pch_gbe_hw *hw);
void pch_gbe_phy_power_up(struct pch_gbe_hw *hw);
void pch_gbe_phy_power_down(struct pch_gbe_hw *hw);
void pch_gbe_phy_set_rgmii(struct pch_gbe_hw *hw);
void pch_gbe_phy_init_setting(struct pch_gbe_hw *hw);

#endif /* _PCH_GBE_PHY_H_ */
