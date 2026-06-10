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
#ifndef _MMC_SD_OPS_H
#define _MMC_SD_OPS_H

int mmc_app_set_bus_width(struct mmc_card *card, int width);
int mmc_send_app_op_cond(struct mmc_host *host, u32 ocr, u32 *rocr);
int mmc_send_if_cond(struct mmc_host *host, u32 ocr);
int mmc_send_relative_addr(struct mmc_host *host, unsigned int *rca);
int mmc_app_send_scr(struct mmc_card *card, u32 *scr);
int mmc_sd_switch(struct mmc_card *card, int mode, int group,
	u8 value, u8 *resp);
int mmc_app_sd_status(struct mmc_card *card, void *ssr);

#endif

