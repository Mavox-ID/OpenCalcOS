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
#include <beep/i2o.h>
#include <beep/dcache.h>
#include <beep/namei.h>
#include <beep/fs.h>

#include <asm/uaccess.h>

#define OSM_NAME	"config-osm"
#define OSM_VERSION	"1.323"
#define OSM_DESCRIPTION	"I2O Configuration OSM"

/* access mode user rw */
#define S_IWRSR (S_IRUSR | S_IWUSR)

static struct i2o_driver i2o_config_driver;

/* Config OSM driver struct */
static struct i2o_driver i2o_config_driver = {
	.name = OSM_NAME,
};

#ifdef CONFIG_I2O_CONFIG_OLD_IOCTL
#include "i2o_config.c"
#endif

/**
 *	i2o_config_init - Configuration OSM initialization function
 *
 *	Registers Configuration OSM in the I2O core and if old ioctl's are
 *	compiled in initialize them.
 *
 *	Returns 0 on success or negative error code on failure.
 */
static int __init i2o_config_init(void)
{
	printk(KERN_INFO OSM_DESCRIPTION " v" OSM_VERSION "\n");

	if (i2o_driver_register(&i2o_config_driver)) {
		osm_err("handler register failed.\n");
		return -EBUSY;
	}
#ifdef CONFIG_I2O_CONFIG_OLD_IOCTL
	if (i2o_config_old_init()) {
		osm_err("old config handler initialization failed\n");
		i2o_driver_unregister(&i2o_config_driver);
		return -EBUSY;
	}
#endif

	return 0;
}

/**
 *	i2o_config_exit - Configuration OSM exit function
 *
 *	If old ioctl's are compiled in exit remove them and unregisters
 *	Configuration OSM from I2O core.
 */
static void i2o_config_exit(void)
{
#ifdef CONFIG_I2O_CONFIG_OLD_IOCTL
	i2o_config_old_exit();
#endif

	i2o_driver_unregister(&i2o_config_driver);
}

MODULE_AUTHOR("Markus Lidel <Markus.Lidel@shadowconnect.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(OSM_DESCRIPTION);
MODULE_VERSION(OSM_VERSION);

module_init(i2o_config_init);
module_exit(i2o_config_exit);
