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
#ifndef _BEEP_WL12XX_H
#define _BEEP_WL12XX_H

/* Reference clock values */
enum {
	WL12XX_REFCLOCK_19	= 0, /* 19.2 MHz */
	WL12XX_REFCLOCK_26	= 1, /* 26 MHz */
	WL12XX_REFCLOCK_38	= 2, /* 38.4 MHz */
	WL12XX_REFCLOCK_52	= 3, /* 52 MHz */
	WL12XX_REFCLOCK_38_XTAL = 4, /* 38.4 MHz, XTAL */
	WL12XX_REFCLOCK_26_XTAL = 5, /* 26 MHz, XTAL */
};

/* TCXO clock values */
enum {
	WL12XX_TCXOCLOCK_19_2	= 0, /* 19.2MHz */
	WL12XX_TCXOCLOCK_26	= 1, /* 26 MHz */
	WL12XX_TCXOCLOCK_38_4	= 2, /* 38.4MHz */
	WL12XX_TCXOCLOCK_52	= 3, /* 52 MHz */
	WL12XX_TCXOCLOCK_16_368	= 4, /* 16.368 MHz */
	WL12XX_TCXOCLOCK_32_736	= 5, /* 32.736 MHz */
	WL12XX_TCXOCLOCK_16_8	= 6, /* 16.8 MHz */
	WL12XX_TCXOCLOCK_33_6	= 7, /* 33.6 MHz */
};

struct wl12xx_platform_data {
	void (*set_power)(bool enable);
	/* SDIO only: IRQ number if WLAN_IRQ line is used, 0 for SDIO IRQs */
	int irq;
	bool use_eeprom;
	int board_ref_clock;
	int board_tcxo_clock;
	unsigned long platform_quirks;
	bool pwr_in_suspend;

	struct wl1271_if_operations *ops;
};

/* Platform does not support level trigger interrupts */
#define WL12XX_PLATFORM_QUIRK_EDGE_IRQ	BIT(0)

#ifdef CONFIG_WL12XX_PLATFORM_DATA

int wl12xx_set_platform_data(const struct wl12xx_platform_data *data);

#else

static inline
int wl12xx_set_platform_data(const struct wl12xx_platform_data *data)
{
	return -ENOSYS;
}

#endif

struct wl12xx_platform_data *wl12xx_get_platform_data(void);

#endif
