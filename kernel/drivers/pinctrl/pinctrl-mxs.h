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
#ifndef __PINCTRL_MXS_H
#define __PINCTRL_MXS_H

#include <beep/platform_device.h>
#include <beep/pinctrl/pinctrl.h>

#define SET	0x4
#define CLR	0x8
#define TOG	0xc

#define MXS_PINCTRL_PIN(pin)	PINCTRL_PIN(pin, #pin)
#define PINID(bank, pin)	((bank) * 32 + (pin))

/*
 * pinmux-id bit field definitions
 *
 * bank:	15..12	(4)
 * pin:		11..4	(8)
 * muxsel:	3..0	(4)
 */
#define MUXID_TO_PINID(m)	PINID((m) >> 12 & 0xf, (m) >> 4 & 0xff)
#define MUXID_TO_MUXSEL(m)	((m) & 0xf)

#define PINID_TO_BANK(p)	((p) >> 5)
#define PINID_TO_PIN(p)		((p) % 32)

/*
 * pin config bit field definitions
 *
 * pull-up:	6..5	(2)
 * voltage:	4..3	(2)
 * mA:		2..0	(3)
 *
 * MSB of each field is presence bit for the config.
 */
#define PULL_PRESENT		(1 << 6)
#define PULL_SHIFT		5
#define VOL_PRESENT		(1 << 4)
#define VOL_SHIFT		3
#define MA_PRESENT		(1 << 2)
#define MA_SHIFT		0
#define CONFIG_TO_PULL(c)	((c) >> PULL_SHIFT & 0x1)
#define CONFIG_TO_VOL(c)	((c) >> VOL_SHIFT & 0x1)
#define CONFIG_TO_MA(c)		((c) >> MA_SHIFT & 0x3)

struct mxs_function {
	const char *name;
	const char **groups;
	unsigned ngroups;
};

struct mxs_group {
	const char *name;
	unsigned int *pins;
	unsigned npins;
	u8 *muxsel;
	u8 config;
};

struct mxs_regs {
	u16 muxsel;
	u16 drive;
	u16 pull;
};

struct mxs_pinctrl_soc_data {
	const struct mxs_regs *regs;
	const struct pinctrl_pin_desc *pins;
	unsigned npins;
	struct mxs_function *functions;
	unsigned nfunctions;
	struct mxs_group *groups;
	unsigned ngroups;
};

int mxs_pinctrl_probe(struct platform_device *pdev,
		      struct mxs_pinctrl_soc_data *soc);
int mxs_pinctrl_remove(struct platform_device *pdev);

#endif /* __PINCTRL_MXS_H */
