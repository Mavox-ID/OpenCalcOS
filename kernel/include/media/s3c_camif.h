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
#ifndef MEDIA_S3C_CAMIF_
#define MEDIA_S3C_CAMIF_

#include <beep/i2c.h>
#include <media/v4l2-mediabus.h>

/**
 * struct s3c_camif_sensor_info - an image sensor description
 * @i2c_board_info: pointer to an I2C sensor subdevice board info
 * @clock_frequency: frequency of the clock the host provides to a sensor
 * @mbus_type: media bus type
 * @i2c_bus_num: i2c control bus id the sensor is attached to
 * @flags: the parallel bus flags defining signals polarity (V4L2_MBUS_*)
 * @use_field: 1 if parallel bus FIELD signal is used (only s3c64xx)
 */
struct s3c_camif_sensor_info {
	struct i2c_board_info i2c_board_info;
	unsigned long clock_frequency;
	enum v4l2_mbus_type mbus_type;
	u16 i2c_bus_num;
	u16 flags;
	u8 use_field;
};

struct s3c_camif_plat_data {
	struct s3c_camif_sensor_info sensor;
	int (*gpio_get)(void);
	int (*gpio_put)(void);
};

/* Platform default helper functions */
int s3c_camif_gpio_get(void);
int s3c_camif_gpio_put(void);

#endif /* MEDIA_S3C_CAMIF_ */
