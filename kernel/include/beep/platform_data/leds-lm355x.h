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
#define LM355x_NAME "leds-lm355x"
#define LM3554_NAME "leds-lm3554"
#define LM3556_NAME "leds-lm3556"

/* lm3554 : strobe def. on */
enum lm355x_strobe {
	LM355x_PIN_STROBE_DISABLE = 0x00,
	LM355x_PIN_STROBE_ENABLE = 0x01,
};

enum lm355x_torch {
	LM355x_PIN_TORCH_DISABLE = 0,
	LM3554_PIN_TORCH_ENABLE = 0x80,
	LM3556_PIN_TORCH_ENABLE = 0x10,
};

enum lm355x_tx2 {
	LM355x_PIN_TX_DISABLE = 0,
	LM3554_PIN_TX_ENABLE = 0x20,
	LM3556_PIN_TX_ENABLE = 0x40,
};

enum lm355x_ntc {
	LM355x_PIN_NTC_DISABLE = 0,
	LM3554_PIN_NTC_ENABLE = 0x08,
	LM3556_PIN_NTC_ENABLE = 0x80,
};

enum lm355x_pmode {
	LM355x_PMODE_DISABLE = 0,
	LM355x_PMODE_ENABLE = 0x04,
};

/*
 * struct lm3554_platform_data
 * @pin_strobe: strobe input
 * @pin_torch : input pin
 *              lm3554-tx1/torch/gpio1
 *              lm3556-torch
 * @pin_tx2   : input pin
 *              lm3554-envm/tx2/gpio2
 *              lm3556-tx pin
 * @ntc_pin  : output pin
 *              lm3554-ledi/ntc
 *              lm3556-temp pin
 * @pass_mode : pass mode
 */
struct lm355x_platform_data {
	enum lm355x_strobe pin_strobe;
	enum lm355x_torch pin_tx1;
	enum lm355x_tx2 pin_tx2;
	enum lm355x_ntc ntc_pin;

	enum lm355x_pmode pass_mode;
};
