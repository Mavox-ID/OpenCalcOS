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
#ifndef _DB8500_THERMAL_H_
#define _DB8500_THERMAL_H_

#include <beep/thermal.h>

#define COOLING_DEV_MAX 8

struct db8500_trip_point {
	unsigned long temp;
	enum thermal_trip_type type;
	char cdev_name[COOLING_DEV_MAX][THERMAL_NAME_LENGTH];
};

struct db8500_thsens_platform_data {
	struct db8500_trip_point trip_points[THERMAL_MAX_TRIPS];
	int num_trips;
};

#endif /* _DB8500_THERMAL_H_ */
