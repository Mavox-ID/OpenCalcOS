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
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/ctype.h>
#include <beep/debugfs.h>
#include <beep/clk.h>
#include "clock.h"

static int clock_debug_rate_set(void *data, u64 val)
{
	struct clk *clock = data;
	int ret;

	/* Only increases to max rate will succeed, but that's actually good
	 * for debugging purposes so we don't check for error. */
	if (clock->flags & CLK_MAX)
		clk_set_max_rate(clock, val);
	if (clock->flags & CLK_MIN)
		ret = clk_set_min_rate(clock, val);
	else
		ret = clk_set_rate(clock, val);
	if (ret != 0)
		printk(KERN_ERR "clk_set%s_rate failed (%d)\n",
			(clock->flags & CLK_MIN) ? "_min" : "", ret);
	return ret;
}

static int clock_debug_rate_get(void *data, u64 *val)
{
	struct clk *clock = data;
	*val = clk_get_rate(clock);
	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(clock_rate_fops, clock_debug_rate_get,
			clock_debug_rate_set, "%llu\n");

static int clock_debug_enable_set(void *data, u64 val)
{
	struct clk *clock = data;
	int rc = 0;

	if (val)
		rc = clock->ops->enable(clock->id);
	else
		clock->ops->disable(clock->id);

	return rc;
}

static int clock_debug_enable_get(void *data, u64 *val)
{
	struct clk *clock = data;

	*val = clock->ops->is_enabled(clock->id);

	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(clock_enable_fops, clock_debug_enable_get,
			clock_debug_enable_set, "%llu\n");

static int clock_debug_local_get(void *data, u64 *val)
{
	struct clk *clock = data;

	*val = clock->ops->is_local(clock->id);

	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(clock_local_fops, clock_debug_local_get,
			NULL, "%llu\n");

static struct dentry *debugfs_base;

int __init clock_debug_init(void)
{
	debugfs_base = debugfs_create_dir("clk", NULL);
	if (!debugfs_base)
		return -ENOMEM;
	return 0;
}

int __init clock_debug_add(struct clk *clock)
{
	char temp[50], *ptr;
	struct dentry *clk_dir;

	if (!debugfs_base)
		return -ENOMEM;

	strncpy(temp, clock->dbg_name, ARRAY_SIZE(temp)-1);
	for (ptr = temp; *ptr; ptr++)
		*ptr = tolower(*ptr);

	clk_dir = debugfs_create_dir(temp, debugfs_base);
	if (!clk_dir)
		return -ENOMEM;

	if (!debugfs_create_file("rate", S_IRUGO | S_IWUSR, clk_dir,
				clock, &clock_rate_fops))
		goto error;

	if (!debugfs_create_file("enable", S_IRUGO | S_IWUSR, clk_dir,
				clock, &clock_enable_fops))
		goto error;

	if (!debugfs_create_file("is_local", S_IRUGO, clk_dir, clock,
				&clock_local_fops))
		goto error;
	return 0;
error:
	debugfs_remove_recursive(clk_dir);
	return -ENOMEM;
}
