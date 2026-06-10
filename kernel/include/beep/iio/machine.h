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
#ifndef __BEEP_IIO_MACHINE_H__
#define __BEEP_IIO_MACHINE_H__

/**
 * struct iio_map - description of link between consumer and device channels
 * @adc_channel_label:	Label used to identify the channel on the provider.
 *			This is matched against the datasheet_name element
 *			of struct iio_chan_spec.
 * @consumer_dev_name:	Name to uniquely identify the consumer device.
 * @consumer_channel:	Unique name used to identify the channel on the
 *			consumer side.
 * @consumer_data:	Data about the channel for use by the consumer driver.
 */
struct iio_map {
	const char *adc_channel_label;
	const char *consumer_dev_name;
	const char *consumer_channel;
	void *consumer_data;
};

#endif
