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
#ifndef __BEEP_LM3642_H
#define __BEEP_LM3642_H

#define LM3642_NAME "leds-lm3642"

enum lm3642_torch_pin_enable {
	LM3642_TORCH_PIN_DISABLE = 0x00,
	LM3642_TORCH_PIN_ENABLE = 0x10,
};

enum lm3642_strobe_pin_enable {
	LM3642_STROBE_PIN_DISABLE = 0x00,
	LM3642_STROBE_PIN_ENABLE = 0x20,
};

enum lm3642_tx_pin_enable {
	LM3642_TX_PIN_DISABLE = 0x00,
	LM3642_TX_PIN_ENABLE = 0x40,
};

struct lm3642_platform_data {
	enum lm3642_torch_pin_enable torch_pin;
	enum lm3642_strobe_pin_enable strobe_pin;
	enum lm3642_tx_pin_enable tx_pin;
};

#endif /* __BEEP_LM3642_H */
