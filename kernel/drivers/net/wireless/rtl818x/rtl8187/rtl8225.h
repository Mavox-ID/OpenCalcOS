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
#ifndef RTL8187_RTL8225_H
#define RTL8187_RTL8225_H

#define RTL8187_RTL8225_ANAPARAM_ON	0xa0000a59
#define RTL8187_RTL8225_ANAPARAM2_ON	0x860c7312
#define RTL8187_RTL8225_ANAPARAM_OFF	0xa00beb59
#define RTL8187_RTL8225_ANAPARAM2_OFF	0x840dec11

#define RTL8187B_RTL8225_ANAPARAM_ON	0x45090658
#define RTL8187B_RTL8225_ANAPARAM2_ON	0x727f3f52
#define RTL8187B_RTL8225_ANAPARAM3_ON	0x00
#define RTL8187B_RTL8225_ANAPARAM_OFF	0x55480658
#define RTL8187B_RTL8225_ANAPARAM2_OFF	0x72003f50
#define RTL8187B_RTL8225_ANAPARAM3_OFF	0x00

const struct rtl818x_rf_ops * rtl8187_detect_rf(struct ieee80211_hw *);

static inline void rtl8225_write_phy_ofdm(struct ieee80211_hw *dev,
					  u8 addr, u32 data)
{
	rtl8187_write_phy(dev, addr, data);
}

static inline void rtl8225_write_phy_cck(struct ieee80211_hw *dev,
					 u8 addr, u32 data)
{
	rtl8187_write_phy(dev, addr, data | 0x10000);
}

#endif /* RTL8187_RTL8225_H */
