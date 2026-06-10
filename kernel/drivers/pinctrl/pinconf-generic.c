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
#define pr_fmt(fmt) "generic pinconfig core: " fmt

#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/device.h>
#include <beep/slab.h>
#include <beep/debugfs.h>
#include <beep/seq_file.h>
#include <beep/pinctrl/pinctrl.h>
#include <beep/pinctrl/pinconf.h>
#include <beep/pinctrl/pinconf-generic.h>
#include "core.h"
#include "pinconf.h"

#ifdef CONFIG_DEBUG_FS

struct pin_config_item {
	const enum pin_config_param param;
	const char * const display;
	const char * const format;
};

#define PCONFDUMP(a, b, c) { .param = a, .display = b, .format = c }

struct pin_config_item conf_items[] = {
	PCONFDUMP(PIN_CONFIG_BIAS_DISABLE, "input bias disabled", NULL),
	PCONFDUMP(PIN_CONFIG_BIAS_HIGH_IMPEDANCE, "input bias high impedance", NULL),
	PCONFDUMP(PIN_CONFIG_BIAS_PULL_UP, "input bias pull up", NULL),
	PCONFDUMP(PIN_CONFIG_BIAS_PULL_DOWN, "input bias pull down", NULL),
	PCONFDUMP(PIN_CONFIG_DRIVE_PUSH_PULL, "output drive push pull", NULL),
	PCONFDUMP(PIN_CONFIG_DRIVE_OPEN_DRAIN, "output drive open drain", NULL),
	PCONFDUMP(PIN_CONFIG_DRIVE_OPEN_SOURCE, "output drive open source", NULL),
	PCONFDUMP(PIN_CONFIG_INPUT_SCHMITT_DISABLE, "input schmitt disabled", NULL),
	PCONFDUMP(PIN_CONFIG_INPUT_SCHMITT, "input schmitt trigger", NULL),
	PCONFDUMP(PIN_CONFIG_INPUT_DEBOUNCE, "input debounce", "time units"),
	PCONFDUMP(PIN_CONFIG_POWER_SOURCE, "pin power source", "selector"),
	PCONFDUMP(PIN_CONFIG_LOW_POWER_MODE, "pin low power", "mode"),
};

void pinconf_generic_dump_pin(struct pinctrl_dev *pctldev,
			      struct seq_file *s, unsigned pin)
{
	const struct pinconf_ops *ops = pctldev->desc->confops;
	int i;

	if (!ops->is_generic)
		return;

	for(i = 0; i < ARRAY_SIZE(conf_items); i++) {
		unsigned long config;
		int ret;

		/* We want to check out this parameter */
		config = pinconf_to_config_packed(conf_items[i].param, 0);
		ret = pin_config_get_for_pin(pctldev, pin, &config);
		/* These are legal errors */
		if (ret == -EINVAL || ret == -ENOTSUPP)
			continue;
		if (ret) {
			seq_printf(s, "ERROR READING CONFIG SETTING %d ", i);
			continue;
		}
		/* Space between multiple configs */
		seq_puts(s, " ");
		seq_puts(s, conf_items[i].display);
		/* Print unit if available */
		if (conf_items[i].format &&
		    pinconf_to_config_argument(config) != 0)
			seq_printf(s, " (%u %s)",
				   pinconf_to_config_argument(config),
				   conf_items[i].format);
	}
}

void pinconf_generic_dump_group(struct pinctrl_dev *pctldev,
			      struct seq_file *s, const char *gname)
{
	const struct pinconf_ops *ops = pctldev->desc->confops;
	int i;

	if (!ops->is_generic)
		return;

	for(i = 0; i < ARRAY_SIZE(conf_items); i++) {
		unsigned long config;
		int ret;

		/* We want to check out this parameter */
		config = pinconf_to_config_packed(conf_items[i].param, 0);
		ret = pin_config_group_get(dev_name(pctldev->dev), gname,
					   &config);
		/* These are legal errors */
		if (ret == -EINVAL || ret == -ENOTSUPP)
			continue;
		if (ret) {
			seq_printf(s, "ERROR READING CONFIG SETTING %d ", i);
			continue;
		}
		/* Space between multiple configs */
		seq_puts(s, " ");
		seq_puts(s, conf_items[i].display);
		/* Print unit if available */
		if (conf_items[i].format && config != 0)
			seq_printf(s, " (%u %s)",
				   pinconf_to_config_argument(config),
				   conf_items[i].format);
	}
}

#endif
