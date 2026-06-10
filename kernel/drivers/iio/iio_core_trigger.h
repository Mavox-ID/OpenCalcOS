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
#ifdef CONFIG_IIO_TRIGGER
/**
 * iio_device_register_trigger_consumer() - set up an iio_dev to use triggers
 * @indio_dev: iio_dev associated with the device that will consume the trigger
 **/
void iio_device_register_trigger_consumer(struct iio_dev *indio_dev);

/**
 * iio_device_unregister_trigger_consumer() - reverse the registration process
 * @indio_dev: iio_dev associated with the device that consumed the trigger
 **/
void iio_device_unregister_trigger_consumer(struct iio_dev *indio_dev);

#else

/**
 * iio_device_register_trigger_consumer() - set up an iio_dev to use triggers
 * @indio_dev: iio_dev associated with the device that will consume the trigger
 **/
static int iio_device_register_trigger_consumer(struct iio_dev *indio_dev)
{
	return 0;
};

/**
 * iio_device_unregister_trigger_consumer() - reverse the registration process
 * @indio_dev: iio_dev associated with the device that consumed the trigger
 **/
static void iio_device_unregister_trigger_consumer(struct iio_dev *indio_dev)
{
};

#endif /* CONFIG_TRIGGER_CONSUMER */



