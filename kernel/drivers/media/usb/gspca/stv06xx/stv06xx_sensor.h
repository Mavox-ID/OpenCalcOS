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
#ifndef STV06XX_SENSOR_H_
#define STV06XX_SENSOR_H_

#include "stv06xx.h"

#define IS_1020(sd)	((sd)->sensor == &stv06xx_sensor_hdcs1020)

extern const struct stv06xx_sensor stv06xx_sensor_vv6410;
extern const struct stv06xx_sensor stv06xx_sensor_hdcs1x00;
extern const struct stv06xx_sensor stv06xx_sensor_hdcs1020;
extern const struct stv06xx_sensor stv06xx_sensor_pb0100;
extern const struct stv06xx_sensor stv06xx_sensor_st6422;

struct stv06xx_sensor {
	/* Defines the name of a sensor */
	char name[32];

	/* Sensor i2c address */
	u8 i2c_addr;

	/* Flush value*/
	u8 i2c_flush;

	/* length of an i2c word */
	u8 i2c_len;

	/* Isoc packet size (per mode) */
	int min_packet_size[4];
	int max_packet_size[4];

	/* Probes if the sensor is connected */
	int (*probe)(struct sd *sd);

	/* Performs a initialization sequence */
	int (*init)(struct sd *sd);

	/* Initializes the controls */
	int (*init_controls)(struct sd *sd);

	/* Reads a sensor register */
	int (*read_sensor)(struct sd *sd, const u8 address,
	      u8 *i2c_data, const u8 len);

	/* Writes to a sensor register */
	int (*write_sensor)(struct sd *sd, const u8 address,
	      u8 *i2c_data, const u8 len);

	/* Instructs the sensor to start streaming */
	int (*start)(struct sd *sd);

	/* Instructs the sensor to stop streaming */
	int (*stop)(struct sd *sd);

	/* Instructs the sensor to dump all its contents */
	int (*dump)(struct sd *sd);
};

#endif
