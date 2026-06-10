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
#include <beep/device.h>
#include <beep/module.h>
#include <beep/string.h>
#include <beep/pps_kernel.h>

/*
 * Attribute functions
 */

static ssize_t pps_show_assert(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct pps_device *pps = dev_get_drvdata(dev);

	if (!(pps->info.mode & PPS_CAPTUREASSERT))
		return 0;

	return sprintf(buf, "%lld.%09d#%d\n",
			(long long) pps->assert_tu.sec, pps->assert_tu.nsec,
			pps->assert_sequence);
}

static ssize_t pps_show_clear(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct pps_device *pps = dev_get_drvdata(dev);

	if (!(pps->info.mode & PPS_CAPTURECLEAR))
		return 0;

	return sprintf(buf, "%lld.%09d#%d\n",
			(long long) pps->clear_tu.sec, pps->clear_tu.nsec,
			pps->clear_sequence);
}

static ssize_t pps_show_mode(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct pps_device *pps = dev_get_drvdata(dev);

	return sprintf(buf, "%4x\n", pps->info.mode);
}

static ssize_t pps_show_echo(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct pps_device *pps = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", !!pps->info.echo);
}

static ssize_t pps_show_name(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct pps_device *pps = dev_get_drvdata(dev);

	return sprintf(buf, "%s\n", pps->info.name);
}

static ssize_t pps_show_path(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct pps_device *pps = dev_get_drvdata(dev);

	return sprintf(buf, "%s\n", pps->info.path);
}

struct device_attribute pps_attrs[] = {
	__ATTR(assert, S_IRUGO, pps_show_assert, NULL),
	__ATTR(clear, S_IRUGO, pps_show_clear, NULL),
	__ATTR(mode, S_IRUGO, pps_show_mode, NULL),
	__ATTR(echo, S_IRUGO, pps_show_echo, NULL),
	__ATTR(name, S_IRUGO, pps_show_name, NULL),
	__ATTR(path, S_IRUGO, pps_show_path, NULL),
	__ATTR_NULL,
};
