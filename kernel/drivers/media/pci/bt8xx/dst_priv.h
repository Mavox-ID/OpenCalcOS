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
struct dst_gpio_enable {
	u32	mask;
	u32	enable;
};

struct dst_gpio_output {
	u32	mask;
	u32	highvals;
};

struct dst_gpio_read {
	unsigned long value;
};

union dst_gpio_packet {
	struct dst_gpio_enable enb;
	struct dst_gpio_output outp;
	struct dst_gpio_read rd;
	int    psize;
};

#define DST_IG_ENABLE	0
#define DST_IG_WRITE	1
#define DST_IG_READ	2
#define DST_IG_TS       3

struct bt878;

int bt878_device_control(struct bt878 *bt, unsigned int cmd, union dst_gpio_packet *mp);
