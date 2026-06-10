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
#ifndef _HID_SENSOR_TRIGGER_H
#define _HID_SENSOR_TRIGGER_H

int hid_sensor_setup_trigger(struct iio_dev *indio_dev, const char *name,
				struct hid_sensor_iio_common *attrb);
void hid_sensor_remove_trigger(struct iio_dev *indio_dev);

#endif
