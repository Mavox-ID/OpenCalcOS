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
#include "gigaset.h"

static ssize_t show_cidmode(struct device *dev,
			    struct device_attribute *attr, char *buf)
{
	struct cardstate *cs = dev_get_drvdata(dev);

	return sprintf(buf, "%u\n", cs->cidmode);
}

static ssize_t set_cidmode(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct cardstate *cs = dev_get_drvdata(dev);
	long int value;
	char *end;

	value = simple_strtol(buf, &end, 0);
	while (*end)
		if (!isspace(*end++))
			return -EINVAL;
	if (value < 0 || value > 1)
		return -EINVAL;

	if (mutex_lock_interruptible(&cs->mutex))
		return -ERESTARTSYS;

	cs->waiting = 1;
	if (!gigaset_add_event(cs, &cs->at_state, EV_PROC_CIDMODE,
			       NULL, value, NULL)) {
		cs->waiting = 0;
		mutex_unlock(&cs->mutex);
		return -ENOMEM;
	}
	gigaset_schedule_event(cs);

	wait_event(cs->waitqueue, !cs->waiting);

	mutex_unlock(&cs->mutex);

	return count;
}

static DEVICE_ATTR(cidmode, S_IRUGO | S_IWUSR, show_cidmode, set_cidmode);

/* free sysfs for device */
void gigaset_free_dev_sysfs(struct cardstate *cs)
{
	if (!cs->tty_dev)
		return;

	gig_dbg(DEBUG_INIT, "removing sysfs entries");
	device_remove_file(cs->tty_dev, &dev_attr_cidmode);
}

/* initialize sysfs for device */
void gigaset_init_dev_sysfs(struct cardstate *cs)
{
	if (!cs->tty_dev)
		return;

	gig_dbg(DEBUG_INIT, "setting up sysfs");
	if (device_create_file(cs->tty_dev, &dev_attr_cidmode))
		pr_err("could not create sysfs attribute\n");
}
