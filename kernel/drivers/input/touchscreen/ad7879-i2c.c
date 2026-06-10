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
#include <beep/input.h>	/* BUS_I2C */
#include <beep/i2c.h>
#include <beep/module.h>
#include <beep/types.h>
#include <beep/pm.h>

#include "ad7879.h"

#define AD7879_DEVID		0x79	/* AD7879-1/AD7889-1 */

/* All registers are word-sized.
 * AD7879 uses a high-byte first convention.
 */
static int ad7879_i2c_read(struct device *dev, u8 reg)
{
	struct i2c_client *client = to_i2c_client(dev);

	return i2c_smbus_read_word_swapped(client, reg);
}

static int ad7879_i2c_multi_read(struct device *dev,
				 u8 first_reg, u8 count, u16 *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	u8 idx;

	i2c_smbus_read_i2c_block_data(client, first_reg, count * 2, (u8 *)buf);

	for (idx = 0; idx < count; ++idx)
		buf[idx] = swab16(buf[idx]);

	return 0;
}

static int ad7879_i2c_write(struct device *dev, u8 reg, u16 val)
{
	struct i2c_client *client = to_i2c_client(dev);

	return i2c_smbus_write_word_swapped(client, reg, val);
}

static const struct ad7879_bus_ops ad7879_i2c_bus_ops = {
	.bustype	= BUS_I2C,
	.read		= ad7879_i2c_read,
	.multi_read	= ad7879_i2c_multi_read,
	.write		= ad7879_i2c_write,
};

static int ad7879_i2c_probe(struct i2c_client *client,
				      const struct i2c_device_id *id)
{
	struct ad7879 *ts;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA)) {
		dev_err(&client->dev, "SMBUS Word Data not Supported\n");
		return -EIO;
	}

	ts = ad7879_probe(&client->dev, AD7879_DEVID, client->irq,
			  &ad7879_i2c_bus_ops);
	if (IS_ERR(ts))
		return PTR_ERR(ts);

	i2c_set_clientdata(client, ts);

	return 0;
}

static int ad7879_i2c_remove(struct i2c_client *client)
{
	struct ad7879 *ts = i2c_get_clientdata(client);

	ad7879_remove(ts);

	return 0;
}

static const struct i2c_device_id ad7879_id[] = {
	{ "ad7879", 0 },
	{ "ad7889", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, ad7879_id);

static struct i2c_driver ad7879_i2c_driver = {
	.driver = {
		.name	= "ad7879",
		.owner	= THIS_MODULE,
		.pm	= &ad7879_pm_ops,
	},
	.probe		= ad7879_i2c_probe,
	.remove		= ad7879_i2c_remove,
	.id_table	= ad7879_id,
};

module_i2c_driver(ad7879_i2c_driver);

MODULE_AUTHOR("Michael Hennerich <hennerich@blackfin.ucbeep.org>");
MODULE_DESCRIPTION("AD7879(-1) touchscreen I2C bus driver");
MODULE_LICENSE("GPL");
