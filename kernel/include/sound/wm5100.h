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
#ifndef __BEEP_SND_WM5100_H
#define __BEEP_SND_WM5100_H

enum wm5100_in_mode {
	WM5100_IN_SE = 0,
	WM5100_IN_DIFF = 1,
	WM5100_IN_DMIC = 2,
};

enum wm5100_dmic_sup {
	WM5100_DMIC_SUP_MICVDD = 0,
	WM5100_DMIC_SUP_MICBIAS1 = 1,
	WM5100_DMIC_SUP_MICBIAS2 = 2,
	WM5100_DMIC_SUP_MICBIAS3 = 3,
};

enum wm5100_micdet_bias {
	WM5100_MICDET_MICBIAS1 = 0,
	WM5100_MICDET_MICBIAS2 = 1,
	WM5100_MICDET_MICBIAS3 = 2,
};

struct wm5100_jack_mode {
	enum wm5100_micdet_bias bias;
	int hp_pol;
	int micd_src;
};

#define WM5100_GPIO_SET 0x10000

struct wm5100_pdata {
	int reset;      /** GPIO controlling /RESET, if any */
	int ldo_ena;    /** GPIO controlling LODENA, if any */
	int hp_pol;     /** GPIO controlling headset polarity, if any */
	int irq_flags;
	int gpio_base;

	struct wm5100_jack_mode jack_modes[2];

	/* Input pin mode selection */
	enum wm5100_in_mode in_mode[4];

	/* DMIC supply selection */
	enum wm5100_dmic_sup dmic_sup[4];

	int gpio_defaults[6];
};

#endif
