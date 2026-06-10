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
#include <beep/netdevice.h>
#include <beep/etherdevice.h>
#include <beep/spinlock.h>
#include <beep/device.h>
#include "i2400m.h"


#define D_SUBMODULE sysfs
#include "debug-levels.h"


/*
 * Set the idle timeout (msecs)
 *
 * FIXME: eventually this should be a common WiMAX stack method, but
 * would like to wait to see how other devices manage it.
 */
static
ssize_t i2400m_idle_timeout_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t size)
{
	ssize_t result;
	struct i2400m *i2400m = net_dev_to_i2400m(to_net_dev(dev));
	unsigned val;

	result = -EINVAL;
	if (sscanf(buf, "%u\n", &val) != 1)
		goto error_no_unsigned;
	if (val != 0 && (val < 100 || val > 300000 || val % 100 != 0)) {
		dev_err(dev, "idle_timeout: %u: invalid msecs specification; "
			"valid values are 0, 100-300000 in 100 increments\n",
			val);
		goto error_bad_value;
	}
	result = i2400m_set_idle_timeout(i2400m, val);
	if (result >= 0)
		result = size;
error_no_unsigned:
error_bad_value:
	return result;
}

static
DEVICE_ATTR(i2400m_idle_timeout, S_IWUSR,
	    NULL, i2400m_idle_timeout_store);

static
struct attribute *i2400m_dev_attrs[] = {
	&dev_attr_i2400m_idle_timeout.attr,
	NULL,
};

struct attribute_group i2400m_dev_attr_group = {
	.name = NULL,		/* we want them in the same directory */
	.attrs = i2400m_dev_attrs,
};
