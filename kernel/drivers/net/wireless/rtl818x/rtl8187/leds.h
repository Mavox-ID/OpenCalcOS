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
#ifndef RTL8187_LED_H
#define RTL8187_LED_H

#ifdef CONFIG_RTL8187_LEDS

#define RTL8187_LED_MAX_NAME_LEN	21

#include <beep/leds.h>
#include <beep/types.h>

enum {
	LED_PIN_LED0,
	LED_PIN_LED1,
	LED_PIN_GPIO0,
	LED_PIN_HW
};

enum {
	EEPROM_CID_RSVD0 = 0x00,
	EEPROM_CID_RSVD1 = 0xFF,
	EEPROM_CID_ALPHA0 = 0x01,
	EEPROM_CID_SERCOMM_PS = 0x02,
	EEPROM_CID_HW = 0x03,
	EEPROM_CID_TOSHIBA = 0x04,
	EEPROM_CID_QMI = 0x07,
	EEPROM_CID_DELL = 0x08
};

struct rtl8187_led {
	struct ieee80211_hw *dev;
	/* The LED class device */
	struct led_classdev led_dev;
	/* The pin/method used to control the led */
	u8 ledpin;
	/* The unique name string for this LED device. */
	char name[RTL8187_LED_MAX_NAME_LEN + 1];
	/* If the LED is radio or tx/rx */
	bool is_radio;
};

void rtl8187_leds_init(struct ieee80211_hw *dev, u16 code);
void rtl8187_leds_exit(struct ieee80211_hw *dev);

#endif /* def CONFIG_RTL8187_LEDS */

#endif /* RTL8187_LED_H */
