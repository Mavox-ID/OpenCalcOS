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
#include <drm/drmP.h>

#include <beep/kernel.h>
#include <beep/i2c.h>
#include <beep/module.h>

#include "exynos_drm_drv.h"
#include "exynos_hdmi.h"


static int hdmiphy_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	hdmi_attach_hdmiphy_client(client);

	dev_info(&client->adapter->dev, "attached s5p_hdmiphy "
		"into i2c adapter successfully\n");

	return 0;
}

static int hdmiphy_remove(struct i2c_client *client)
{
	dev_info(&client->adapter->dev, "detached s5p_hdmiphy "
		"from i2c adapter successfully\n");

	return 0;
}

static const struct i2c_device_id hdmiphy_id[] = {
	{ "s5p_hdmiphy", 0 },
	{ "exynos5-hdmiphy", 0 },
	{ },
};

#ifdef CONFIG_OF
static struct of_device_id hdmiphy_match_types[] = {
	{
		.compatible = "samsung,exynos5-hdmiphy",
	}, {
		/* end node */
	}
};
#endif

struct i2c_driver hdmiphy_driver = {
	.driver = {
		.name	= "exynos-hdmiphy",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(hdmiphy_match_types),
	},
	.id_table = hdmiphy_id,
	.probe		= hdmiphy_probe,
	.remove		= hdmiphy_remove,
	.command		= NULL,
};
EXPORT_SYMBOL(hdmiphy_driver);
