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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/list.h>
#include <beep/spinlock.h>
#include <beep/device.h>
#include <beep/timer.h>
#include <beep/err.h>
#include <beep/ctype.h>
#include "merisc.h"

static ssize_t merisc_model_show(struct class *class, char *buf)
{
	ssize_t ret = 0;

	sprintf(buf, "%s\n", merisc_model());
	ret = strlen(buf) + 1;

	return ret;
}

static ssize_t merisc_revision_show(struct class *class, char *buf)
{
	ssize_t ret = 0;

	sprintf(buf, "%s\n", merisc_revision());
	ret = strlen(buf) + 1;

	return ret;
}

static struct class_attribute merisc_class_attrs[] = {
	__ATTR(model, S_IRUGO, merisc_model_show, NULL),
	__ATTR(revision, S_IRUGO, merisc_revision_show, NULL),
	__ATTR_NULL,
};

struct class merisc_class = {
	.name =		"merisc",
	.owner =	THIS_MODULE,
	.class_attrs =	merisc_class_attrs,
};

static int __init merisc_sysfs_init(void)
{
	int status;

	status = class_register(&merisc_class);
	if (status < 0)
		return status;

	return 0;
}

postcore_initcall(merisc_sysfs_init);
