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
#ifndef SPI_AD5624R_H_
#define SPI_AD5624R_H_

#define AD5624R_DAC_CHANNELS			4

#define AD5624R_ADDR_DAC0			0x0
#define AD5624R_ADDR_DAC1			0x1
#define AD5624R_ADDR_DAC2			0x2
#define AD5624R_ADDR_DAC3			0x3
#define AD5624R_ADDR_ALL_DAC			0x7

#define AD5624R_CMD_WRITE_INPUT_N		0x0
#define AD5624R_CMD_UPDATE_DAC_N		0x1
#define AD5624R_CMD_WRITE_INPUT_N_UPDATE_ALL	0x2
#define AD5624R_CMD_WRITE_INPUT_N_UPDATE_N	0x3
#define AD5624R_CMD_POWERDOWN_DAC		0x4
#define AD5624R_CMD_RESET			0x5
#define AD5624R_CMD_LDAC_SETUP			0x6
#define AD5624R_CMD_INTERNAL_REFER_SETUP	0x7

#define AD5624R_LDAC_PWRDN_NONE			0x0
#define AD5624R_LDAC_PWRDN_1K			0x1
#define AD5624R_LDAC_PWRDN_100K			0x2
#define AD5624R_LDAC_PWRDN_3STATE		0x3

/**
 * struct ad5624r_chip_info - chip specific information
 * @channels:		channel spec for the DAC
 * @int_vref_mv:	AD5620/40/60: the internal reference voltage
 */

struct ad5624r_chip_info {
	const struct iio_chan_spec	*channels;
	u16				int_vref_mv;
};

/**
 * struct ad5446_state - driver instance specific data
 * @indio_dev:		the industrial I/O device
 * @us:			spi_device
 * @chip_info:		chip model specific constants, available modes etc
 * @reg:		supply regulator
 * @vref_mv:		actual reference voltage used
 * @pwr_down_mask	power down mask
 * @pwr_down_mode	current power down mode
 */

struct ad5624r_state {
	struct spi_device		*us;
	const struct ad5624r_chip_info	*chip_info;
	struct regulator		*reg;
	unsigned short			vref_mv;
	unsigned			pwr_down_mask;
	unsigned			pwr_down_mode;
};

/**
 * ad5624r_supported_device_ids:
 * The AD5624/44/64 parts are available in different
 * fixed internal reference voltage options.
 */

enum ad5624r_supported_device_ids {
	ID_AD5624R3,
	ID_AD5644R3,
	ID_AD5664R3,
	ID_AD5624R5,
	ID_AD5644R5,
	ID_AD5664R5,
};

#endif /* SPI_AD5624R_H_ */
