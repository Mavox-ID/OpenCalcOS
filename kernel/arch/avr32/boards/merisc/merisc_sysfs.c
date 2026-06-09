/*
 * Merisc sysfs exports
 *
 * Copyright (C) 2008 Martinsson Elektronik AB
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
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
