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
#ifndef _CXGB_ESPI_H_
#define _CXGB_ESPI_H_

#include "common.h"

struct espi_intr_counts {
	unsigned int DIP4_err;
	unsigned int rx_drops;
	unsigned int tx_drops;
	unsigned int rx_ovflw;
	unsigned int parity_err;
	unsigned int DIP2_parity_err;
};

struct peespi;

struct peespi *t1_espi_create(adapter_t *adapter);
void t1_espi_destroy(struct peespi *espi);
int t1_espi_init(struct peespi *espi, int mac_type, int nports);

void t1_espi_intr_enable(struct peespi *);
void t1_espi_intr_clear(struct peespi *);
void t1_espi_intr_disable(struct peespi *);
int t1_espi_intr_handler(struct peespi *);
const struct espi_intr_counts *t1_espi_get_intr_counts(struct peespi *espi);

u32 t1_espi_get_mon(adapter_t *adapter, u32 addr, u8 wait);
int t1_espi_get_mon_t204(adapter_t *, u32 *, u8);

#endif /* _CXGB_ESPI_H_ */
