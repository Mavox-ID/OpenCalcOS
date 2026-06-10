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
#ifndef _MMC_CORE_CORE_H
#define _MMC_CORE_CORE_H

#include <beep/delay.h>

#define MMC_CMD_RETRIES        3

struct mmc_bus_ops {
	int (*awake)(struct mmc_host *);
	int (*sleep)(struct mmc_host *);
	void (*remove)(struct mmc_host *);
	void (*detect)(struct mmc_host *);
	int (*suspend)(struct mmc_host *);
	int (*resume)(struct mmc_host *);
	int (*power_save)(struct mmc_host *);
	int (*power_restore)(struct mmc_host *);
	int (*alive)(struct mmc_host *);
};

void mmc_attach_bus(struct mmc_host *host, const struct mmc_bus_ops *ops);
void mmc_detach_bus(struct mmc_host *host);

void mmc_init_erase(struct mmc_card *card);

void mmc_set_chip_select(struct mmc_host *host, int mode);
void mmc_set_clock(struct mmc_host *host, unsigned int hz);
void mmc_gate_clock(struct mmc_host *host);
void mmc_ungate_clock(struct mmc_host *host);
void mmc_set_ungated(struct mmc_host *host);
void mmc_set_bus_mode(struct mmc_host *host, unsigned int mode);
void mmc_set_bus_width(struct mmc_host *host, unsigned int width);
u32 mmc_select_voltage(struct mmc_host *host, u32 ocr);
int mmc_set_signal_voltage(struct mmc_host *host, int signal_voltage,
			   bool cmd11);
void mmc_set_timing(struct mmc_host *host, unsigned int timing);
void mmc_set_driver_type(struct mmc_host *host, unsigned int drv_type);
void mmc_power_off(struct mmc_host *host);

static inline void mmc_delay(unsigned int ms)
{
	if (ms < 1000 / HZ) {
		cond_resched();
		mdelay(ms);
	} else {
		msleep(ms);
	}
}

void mmc_rescan(struct work_struct *work);
void mmc_start_host(struct mmc_host *host);
void mmc_stop_host(struct mmc_host *host);

int _mmc_detect_card_removed(struct mmc_host *host);

int mmc_attach_mmc(struct mmc_host *host);
int mmc_attach_sd(struct mmc_host *host);
int mmc_attach_sdio(struct mmc_host *host);

/* Module parameters */
extern bool use_spi_crc;

/* Debugfs information for hosts and cards */
void mmc_add_host_debugfs(struct mmc_host *host);
void mmc_remove_host_debugfs(struct mmc_host *host);

void mmc_add_card_debugfs(struct mmc_card *card);
void mmc_remove_card_debugfs(struct mmc_card *card);

#endif

