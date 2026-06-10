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
#define pr_fmt(fmt)	"mop500-uib: " fmt

#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/i2c.h>

#include <mach/hardware.h>
#include "board-mop500.h"

enum mop500_uib {
	STUIB,
	U8500UIB,
};

struct uib {
	const char *name;
	const char *option;
	void (*init)(void);
};

static struct uib __initdata mop500_uibs[] = {
	[STUIB] = {
		.name	= "ST-UIB",
		.option	= "stuib",
		.init	= mop500_stuib_init,
	},
	[U8500UIB] = {
		.name	= "U8500-UIB",
		.option	= "u8500uib",
		.init	= mop500_u8500uib_init,
	},
};

static struct uib *mop500_uib;

static int __init mop500_uib_setup(char *str)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(mop500_uibs); i++) {
		struct uib *uib = &mop500_uibs[i];

		if (!strcmp(str, uib->option)) {
			mop500_uib = uib;
			break;
		}
	}

	if (i == ARRAY_SIZE(mop500_uibs))
		pr_err("invalid uib= option (%s)\n", str);

	return 1;
}
__setup("uib=", mop500_uib_setup);

/*
 * The UIBs are detected after the I2C host controllers are registered, so
 * i2c_register_board_info() can't be used.
 */
void mop500_uib_i2c_add(int busnum, struct i2c_board_info *info,
		unsigned n)
{
	struct i2c_adapter *adap;
	struct i2c_client *client;
	int i;

	adap = i2c_get_adapter(busnum);
	if (!adap) {
		pr_err("failed to get adapter i2c%d\n", busnum);
		return;
	}

	for (i = 0; i < n; i++) {
		client = i2c_new_device(adap, &info[i]);
		if (!client)
			pr_err("failed to register %s to i2c%d\n",
					info[i].type, busnum);
	}

	i2c_put_adapter(adap);
}

static void __init __mop500_uib_init(struct uib *uib, const char *why)
{
	pr_info("%s (%s)\n", uib->name, why);
	uib->init();
}

/*
 * Detect the UIB attached based on the presence or absence of i2c devices.
 */
int __init mop500_uib_init(void)
{
	struct uib *uib = mop500_uib;
	struct i2c_adapter *i2c0;
	int ret;

	if (!cpu_is_u8500_family())
		return -ENODEV;

	if (uib) {
		__mop500_uib_init(uib, "from uib= boot argument");
		return 0;
	}

	i2c0 = i2c_get_adapter(0);
	if (!i2c0) {
		__mop500_uib_init(&mop500_uibs[STUIB],
				"fallback, could not get i2c0");
		return -ENODEV;
	}

	/* U8500-UIB has the TC35893 at 0x44 on I2C0, the ST-UIB doesn't. */
	ret = i2c_smbus_xfer(i2c0, 0x44, 0, I2C_SMBUS_WRITE, 0,
			I2C_SMBUS_QUICK, NULL);
	i2c_put_adapter(i2c0);

	if (ret == 0)
		uib = &mop500_uibs[U8500UIB];
	else
		uib = &mop500_uibs[STUIB];

	__mop500_uib_init(uib, "detected");

	return 0;
}
