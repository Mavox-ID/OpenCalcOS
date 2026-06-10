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
#include "dvb-usb-common.h"

int dvb_usb_i2c_init(struct dvb_usb_device *d)
{
	int ret = 0;

	if (!(d->props.caps & DVB_USB_IS_AN_I2C_ADAPTER))
		return 0;

	if (d->props.i2c_algo == NULL) {
		err("no i2c algorithm specified");
		return -EINVAL;
	}

	strlcpy(d->i2c_adap.name, d->desc->name, sizeof(d->i2c_adap.name));
	d->i2c_adap.algo      = d->props.i2c_algo;
	d->i2c_adap.algo_data = NULL;
	d->i2c_adap.dev.parent = &d->udev->dev;

	i2c_set_adapdata(&d->i2c_adap, d);

	if ((ret = i2c_add_adapter(&d->i2c_adap)) < 0)
		err("could not add i2c adapter");

	d->state |= DVB_USB_STATE_I2C;

	return ret;
}

int dvb_usb_i2c_exit(struct dvb_usb_device *d)
{
	if (d->state & DVB_USB_STATE_I2C)
		i2c_del_adapter(&d->i2c_adap);
	d->state &= ~DVB_USB_STATE_I2C;
	return 0;
}
