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
#include <beep/device.h>
#include <beep/types.h>
#include <beep/superhyway.h>

#define superhyway_ro_attr(name, fmt, field)				\
static ssize_t name##_show(struct device *dev, struct device_attribute *attr, char *buf)		\
{									\
	struct superhyway_device *s = to_superhyway_device(dev);	\
	return sprintf(buf, fmt, s->field);				\
}

/* VCR flags */
superhyway_ro_attr(perr_flags, "0x%02x\n", vcr.perr_flags);
superhyway_ro_attr(merr_flags, "0x%02x\n", vcr.merr_flags);
superhyway_ro_attr(mod_vers, "0x%04x\n", vcr.mod_vers);
superhyway_ro_attr(mod_id, "0x%04x\n", vcr.mod_id);
superhyway_ro_attr(bot_mb, "0x%02x\n", vcr.bot_mb);
superhyway_ro_attr(top_mb, "0x%02x\n", vcr.top_mb);

/* Misc */
superhyway_ro_attr(resource, "0x%08lx\n", resource[0].start);

struct device_attribute superhyway_dev_attrs[] = {
	__ATTR_RO(perr_flags),
	__ATTR_RO(merr_flags),
	__ATTR_RO(mod_vers),
	__ATTR_RO(mod_id),
	__ATTR_RO(bot_mb),
	__ATTR_RO(top_mb),
	__ATTR_RO(resource),
	__ATTR_NULL,
};

