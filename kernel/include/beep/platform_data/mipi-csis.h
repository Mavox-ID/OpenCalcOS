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
#ifndef __PLAT_SAMSUNG_MIPI_CSIS_H_
#define __PLAT_SAMSUNG_MIPI_CSIS_H_ __FILE__

/**
 * struct s5p_platform_mipi_csis - platform data for S5P MIPI-CSIS driver
 * @clk_rate:    bus clock frequency
 * @wclk_source: CSI wrapper clock selection: 0 - bus clock, 1 - ext. SCLK_CAM
 * @lanes:       number of data lanes used
 * @hs_settle:   HS-RX settle time
 */
struct s5p_platform_mipi_csis {
	unsigned long clk_rate;
	u8 wclk_source;
	u8 lanes;
	u8 hs_settle;
};

/**
 * s5p_csis_phy_enable - global MIPI-CSI receiver D-PHY control
 * @id:     MIPI-CSIS harware instance index (0...1)
 * @on:     true to enable D-PHY and deassert its reset
 *          false to disable D-PHY
 * @return: 0 on success, or negative error code on failure
 */
int s5p_csis_phy_enable(int id, bool on);

#endif /* __PLAT_SAMSUNG_MIPI_CSIS_H_ */
