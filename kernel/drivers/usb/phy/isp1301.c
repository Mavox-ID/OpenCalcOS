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
#include <beep/module.h>
#include <beep/i2c.h>

#define DRV_NAME		"isp1301"

static const struct i2c_device_id isp1301_id[] = {
	{ "isp1301", 0 },
	{ }
};

static struct i2c_client *isp1301_i2c_client;

static int isp1301_probe(struct i2c_client *client,
			 const struct i2c_device_id *i2c_id)
{
	isp1301_i2c_client = client;
	return 0;
}

static int isp1301_remove(struct i2c_client *client)
{
	return 0;
}

static struct i2c_driver isp1301_driver = {
	.driver = {
		.name = DRV_NAME,
	},
	.probe = isp1301_probe,
	.remove = isp1301_remove,
	.id_table = isp1301_id,
};

module_i2c_driver(isp1301_driver);

static int match(struct device *dev, void *data)
{
	struct device_node *node = (struct device_node *)data;
	return (dev->of_node == node) &&
		(dev->driver == &isp1301_driver.driver);
}

struct i2c_client *isp1301_get_client(struct device_node *node)
{
	if (node) { /* reference of ISP1301 I2C node via DT */
		struct device *dev = bus_find_device(&i2c_bus_type, NULL,
						     node, match);
		if (!dev)
			return NULL;
		return to_i2c_client(dev);
	} else { /* non-DT: only one ISP1301 chip supported */
		return isp1301_i2c_client;
	}
}
EXPORT_SYMBOL_GPL(isp1301_get_client);

MODULE_AUTHOR("Roland Stigge <stigge@antcom.de>");
MODULE_DESCRIPTION("NXP ISP1301 USB transceiver driver");
MODULE_LICENSE("GPL");
