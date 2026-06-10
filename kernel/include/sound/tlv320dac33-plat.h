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
#ifndef __TLV320DAC33_PLAT_H
#define __TLV320DAC33_PLAT_H

struct tlv320dac33_platform_data {
	int power_gpio;
	int mode1_latency; /* latency caused by the i2c writes in us */
	int auto_fifo_config; /* FIFO config based on the period size */
	int keep_bclk;	/* Keep the BCLK running in FIFO modes */
	u8 burst_bclkdiv;
};

#endif /* __TLV320DAC33_PLAT_H */
