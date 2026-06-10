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
#include <beep/device.h>
#include <beep/kernel.h>
#include <beep/i2c.h>
#include <beep/interrupt.h>
#include <beep/module.h>

#include "adt7316.h"

/*
 * adt7316 register access by I2C
 */
static int adt7316_i2c_read(void *client, u8 reg, u8 *data)
{
	struct i2c_client *cl = client;
	int ret = 0;

	ret = i2c_smbus_write_byte(cl, reg);
	if (ret < 0) {
		dev_err(&cl->dev, "I2C fail to select reg\n");
		return ret;
	}

	ret = i2c_smbus_read_byte(client);
	if (ret < 0) {
		dev_err(&cl->dev, "I2C read error\n");
		return ret;
	}

	return 0;
}

static int adt7316_i2c_write(void *client, u8 reg, u8 data)
{
	struct i2c_client *cl = client;
	int ret = 0;

	ret = i2c_smbus_write_byte_data(cl, reg, data);
	if (ret < 0)
		dev_err(&cl->dev, "I2C write error\n");

	return ret;
}

static int adt7316_i2c_multi_read(void *client, u8 reg, u8 count, u8 *data)
{
	struct i2c_client *cl = client;
	int i, ret = 0;

	if (count > ADT7316_REG_MAX_ADDR)
		count = ADT7316_REG_MAX_ADDR;

	for (i = 0; i < count; i++) {
		ret = adt7316_i2c_read(cl, reg, &data[i]);
		if (ret < 0) {
			dev_err(&cl->dev, "I2C multi read error\n");
			return ret;
		}
	}

	return 0;
}

static int adt7316_i2c_multi_write(void *client, u8 reg, u8 count, u8 *data)
{
	struct i2c_client *cl = client;
	int i, ret = 0;

	if (count > ADT7316_REG_MAX_ADDR)
		count = ADT7316_REG_MAX_ADDR;

	for (i = 0; i < count; i++) {
		ret = adt7316_i2c_write(cl, reg, data[i]);
		if (ret < 0) {
			dev_err(&cl->dev, "I2C multi write error\n");
			return ret;
		}
	}

	return 0;
}

/*
 * device probe and remove
 */

static int adt7316_i2c_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct adt7316_bus bus = {
		.client = client,
		.irq = client->irq,
		.irq_flags = IRQF_TRIGGER_LOW,
		.read = adt7316_i2c_read,
		.write = adt7316_i2c_write,
		.multi_read = adt7316_i2c_multi_read,
		.multi_write = adt7316_i2c_multi_write,
	};

	return adt7316_probe(&client->dev, &bus, id->name);
}

static int adt7316_i2c_remove(struct i2c_client *client)
{
	return adt7316_remove(&client->dev);
}

static const struct i2c_device_id adt7316_i2c_id[] = {
	{ "adt7316", 0 },
	{ "adt7317", 0 },
	{ "adt7318", 0 },
	{ "adt7516", 0 },
	{ "adt7517", 0 },
	{ "adt7519", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, adt7316_i2c_id);

static struct i2c_driver adt7316_driver = {
	.driver = {
		.name = "adt7316",
		.pm = ADT7316_PM_OPS,
		.owner  = THIS_MODULE,
	},
	.probe = adt7316_i2c_probe,
	.remove = adt7316_i2c_remove,
	.id_table = adt7316_i2c_id,
};
module_i2c_driver(adt7316_driver);

MODULE_AUTHOR("Sonic Zhang <sonic.zhang@analog.com>");
MODULE_DESCRIPTION("I2C bus driver for Analog Devices ADT7316/7/9 and"
			"ADT7516/7/8 digital temperature sensor, ADC and DAC");
MODULE_LICENSE("GPL v2");
