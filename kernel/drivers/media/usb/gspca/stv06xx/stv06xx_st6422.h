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
#ifndef STV06XX_ST6422_H_
#define STV06XX_ST6422_H_

#include "stv06xx_sensor.h"

static int st6422_probe(struct sd *sd);
static int st6422_start(struct sd *sd);
static int st6422_init(struct sd *sd);
static int st6422_init_controls(struct sd *sd);
static int st6422_stop(struct sd *sd);

const struct stv06xx_sensor stv06xx_sensor_st6422 = {
	.name = "ST6422",
	/* No known way to lower framerate in case of less bandwidth */
	.min_packet_size = { 300, 847 },
	.max_packet_size = { 300, 847 },
	.init = st6422_init,
	.init_controls = st6422_init_controls,
	.probe = st6422_probe,
	.start = st6422_start,
	.stop = st6422_stop,
};

#endif
