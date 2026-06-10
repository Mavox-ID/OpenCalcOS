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
#ifndef _ADXL34X_H_
#define _ADXL34X_H_

struct device;
struct adxl34x;

struct adxl34x_bus_ops {
	u16 bustype;
	int (*read)(struct device *, unsigned char);
	int (*read_block)(struct device *, unsigned char, int, void *);
	int (*write)(struct device *, unsigned char, unsigned char);
};

void adxl34x_suspend(struct adxl34x *ac);
void adxl34x_resume(struct adxl34x *ac);
struct adxl34x *adxl34x_probe(struct device *dev, int irq,
			      bool fifo_delay_default,
			      const struct adxl34x_bus_ops *bops);
int adxl34x_remove(struct adxl34x *ac);

#endif
