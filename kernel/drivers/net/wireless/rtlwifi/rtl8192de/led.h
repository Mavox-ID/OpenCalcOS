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
#ifndef __RTL92CE_LED_H__
#define __RTL92CE_LED_H__

void rtl92de_init_sw_leds(struct ieee80211_hw *hw);
void rtl92de_sw_led_on(struct ieee80211_hw *hw, struct rtl_led *pled);
void rtl92de_sw_led_off(struct ieee80211_hw *hw, struct rtl_led *pled);
void rtl92de_led_control(struct ieee80211_hw *hw, enum led_ctl_mode ledaction);

#endif
