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
#ifndef _PXA_SDHCI_H_
#define _PXA_SDHCI_H_

/* pxa specific flag */
/* Require clock free running */
#define PXA_FLAG_ENABLE_CLOCK_GATING (1<<0)
/* card always wired to host, like on-chip emmc */
#define PXA_FLAG_CARD_PERMANENT	(1<<1)
/* Board design supports 8-bit data on SD/SDIO BUS */
#define PXA_FLAG_SD_8_BIT_CAPABLE_SLOT (1<<2)

/*
 * struct pxa_sdhci_platdata() - Platform device data for PXA SDHCI
 * @flags: flags for platform requirement
 * @clk_delay_cycles:
 *	mmp2: each step is roughly 100ps, 5bits width
 *	pxa910: each step is 1ns, 4bits width
 * @clk_delay_sel: select clk_delay, used on pxa910
 *	0: choose feedback clk
 *	1: choose feedback clk + delay value
 *	2: choose internal clk
 * @clk_delay_enable: enable clk_delay or not, used on pxa910
 * @ext_cd_gpio: gpio pin used for external CD line
 * @ext_cd_gpio_invert: invert values for external CD gpio line
 * @max_speed: the maximum speed supported
 * @host_caps: Standard MMC host capabilities bit field.
 * @quirks: quirks of platfrom
 * @quirks2: quirks2 of platfrom
 * @pm_caps: pm_caps of platfrom
 */
struct sdhci_pxa_platdata {
	unsigned int	flags;
	unsigned int	clk_delay_cycles;
	unsigned int	clk_delay_sel;
	bool		clk_delay_enable;
	unsigned int	ext_cd_gpio;
	bool		ext_cd_gpio_invert;
	unsigned int	max_speed;
	u32		host_caps;
	u32		host_caps2;
	unsigned int	quirks;
	unsigned int	quirks2;
	unsigned int	pm_caps;
};

struct sdhci_pxa {
	u8	clk_enable;
	u8	power_mode;
};
#endif /* _PXA_SDHCI_H_ */
