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
#ifndef SI4713_H
#define SI4713_H

/* The SI4713 I2C sensor chip has a fixed slave address of 0xc6 or 0x22. */
#define SI4713_I2C_ADDR_BUSEN_HIGH	0x63
#define SI4713_I2C_ADDR_BUSEN_LOW	0x11

/*
 * Platform dependent definition
 */
struct si4713_platform_data {
	int gpio_reset; /* < 0 if not used */
};

/*
 * Structure to query for Received Noise Level (RNL).
 */
struct si4713_rnl {
	__u32 index;		/* modulator index */
	__u32 frequency;	/* frequency to peform rnl measurement */
	__s32 rnl;		/* result of measurement in dBuV */
	__u32 reserved[4];	/* drivers and apps must init this to 0 */
};

/*
 * This is the ioctl number to query for rnl. Users must pass a
 * struct si4713_rnl pointer specifying desired frequency in 'frequency' field
 * following driver capabilities (i.e V4L2_TUNER_CAP_LOW).
 * Driver must return measured value in the same struture, filling 'rnl' field.
 */
#define SI4713_IOC_MEASURE_RNL	_IOWR('V', BASE_VIDIOC_PRIVATE + 0, \
						struct si4713_rnl)

#endif /* ifndef SI4713_H*/
