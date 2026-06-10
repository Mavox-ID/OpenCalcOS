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
#ifndef _AD714X_H_
#define _AD714X_H_

#include <beep/types.h>

#define STAGE_NUM              12

struct device;
struct ad714x_platform_data;
struct ad714x_driver_data;
struct ad714x_chip;

typedef int (*ad714x_read_t)(struct ad714x_chip *, unsigned short, unsigned short *, size_t);
typedef int (*ad714x_write_t)(struct ad714x_chip *, unsigned short, unsigned short);

struct ad714x_chip {
	unsigned short l_state;
	unsigned short h_state;
	unsigned short c_state;
	unsigned short adc_reg[STAGE_NUM];
	unsigned short amb_reg[STAGE_NUM];
	unsigned short sensor_val[STAGE_NUM];

	struct ad714x_platform_data *hw;
	struct ad714x_driver_data *sw;

	int irq;
	struct device *dev;
	ad714x_read_t read;
	ad714x_write_t write;

	struct mutex mutex;

	unsigned product;
	unsigned version;

	__be16 xfer_buf[16] ____cacheline_aligned;

};

int ad714x_disable(struct ad714x_chip *ad714x);
int ad714x_enable(struct ad714x_chip *ad714x);
struct ad714x_chip *ad714x_probe(struct device *dev, u16 bus_type, int irq,
				 ad714x_read_t read, ad714x_write_t write);
void ad714x_remove(struct ad714x_chip *ad714x);

#endif
