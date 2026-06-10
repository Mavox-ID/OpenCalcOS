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
#ifndef _MMC_CORE_SDIO_BUS_H
#define _MMC_CORE_SDIO_BUS_H

struct sdio_func *sdio_alloc_func(struct mmc_card *card);
int sdio_add_func(struct sdio_func *func);
void sdio_remove_func(struct sdio_func *func);

int sdio_register_bus(void);
void sdio_unregister_bus(void);

#endif

