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
#include "cyttsp_core.h"

#include <beep/i2c.h>
#include <beep/input.h>

#define CY_I2C_DATA_SIZE	128

static int cyttsp_i2c_read_block_data(struct cyttsp *ts,
				      u8 addr, u8 length, void *values)
{
	struct i2c_client *client = to_i2c_client(ts->dev);
	struct i2c_msg msgs[] = {
		{
			.addr = client->addr,
			.flags = 0,
			.len = 1,
			.buf = &addr,
		},
		{
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = length,
			.buf = values,
		},
	};
	int retval;

	retval = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	if (retval < 0)
		return retval;

	return retval != ARRAY_SIZE(msgs) ? -EIO : 0;
}

static int cyttsp_i2c_write_block_data(struct cyttsp *ts,
				       u8 addr, u8 length, const void *values)
{
	struct i2c_client *client = to_i2c_client(ts->dev);
	int retval;

	ts->xfer_buf[0] = addr;
	memcpy(&ts->xfer_buf[1], values, length);

	retval = i2c_master_send(client, ts->xfer_buf, length + 1);

	return retval < 0 ? retval : 0;
}

static const struct cyttsp_bus_ops cyttsp_i2c_bus_ops = {
	.bustype	= BUS_I2C,
	.write		= cyttsp_i2c_write_block_data,
	.read           = cyttsp_i2c_read_block_data,
};

static int cyttsp_i2c_probe(struct i2c_client *client,
				      const struct i2c_device_id *id)
{
	struct cyttsp *ts;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "I2C functionality not Supported\n");
		return -EIO;
	}

	ts = cyttsp_probe(&cyttsp_i2c_bus_ops, &client->dev, client->irq,
			  CY_I2C_DATA_SIZE);

	if (IS_ERR(ts))
		return PTR_ERR(ts);

	i2c_set_clientdata(client, ts);

	return 0;
}

static int cyttsp_i2c_remove(struct i2c_client *client)
{
	struct cyttsp *ts = i2c_get_clientdata(client);

	cyttsp_remove(ts);

	return 0;
}

static const struct i2c_device_id cyttsp_i2c_id[] = {
	{ CY_I2C_NAME, 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, cyttsp_i2c_id);

static struct i2c_driver cyttsp_i2c_driver = {
	.driver = {
		.name	= CY_I2C_NAME,
		.owner	= THIS_MODULE,
		.pm	= &cyttsp_pm_ops,
	},
	.probe		= cyttsp_i2c_probe,
	.remove		= cyttsp_i2c_remove,
	.id_table	= cyttsp_i2c_id,
};

module_i2c_driver(cyttsp_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Cypress TrueTouch(R) Standard Product (TTSP) I2C driver");
MODULE_AUTHOR("Cypress");
MODULE_ALIAS("i2c:cyttsp");
