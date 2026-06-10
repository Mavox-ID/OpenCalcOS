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
#ifndef PHY_H
#define PHY_H

#define CHANSEL_DIV		15
#define CHANSEL_2G(_freq)	(((_freq) * 0x10000) / CHANSEL_DIV)
#define CHANSEL_5G(_freq)	(((_freq) * 0x8000) / CHANSEL_DIV)

#define AR_PHY_BASE     0x9800
#define AR_PHY(_n)      (AR_PHY_BASE + ((_n)<<2))

#define AR_PHY_TX_PWRCTRL_TX_GAIN_TAB_MAX   0x0007E000
#define AR_PHY_TX_PWRCTRL_TX_GAIN_TAB_MAX_S 13
#define AR_PHY_TX_GAIN_CLC       0x0000001E
#define AR_PHY_TX_GAIN_CLC_S     1
#define AR_PHY_TX_GAIN           0x0007F000
#define AR_PHY_TX_GAIN_S         12

#define AR_PHY_CLC_TBL1      0xa35c
#define AR_PHY_CLC_I0        0x07ff0000
#define AR_PHY_CLC_I0_S      16
#define AR_PHY_CLC_Q0        0x0000ffd0
#define AR_PHY_CLC_Q0_S      5

#define ANTSWAP_AB 0x0001
#define REDUCE_CHAIN_0 0x00000050
#define REDUCE_CHAIN_1 0x00000051
#define AR_PHY_CHIP_ID 0x9818

#define	AR_PHY_TIMING11_SPUR_FREQ_SD		0x3FF00000
#define	AR_PHY_TIMING11_SPUR_FREQ_SD_S		20

#define AR_PHY_PLL_CONTROL 0x16180
#define AR_PHY_PLL_MODE 0x16184

#endif
