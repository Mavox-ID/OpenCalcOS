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
#include <beep/mutex.h>
#include <beep/module.h>
#include <beep/cpuidle.h>

#include "cpuidle.h"

LIST_HEAD(cpuidle_governors);
struct cpuidle_governor *cpuidle_curr_governor;

/**
 * __cpuidle_find_governor - finds a governor of the specified name
 * @str: the name
 *
 * Must be called with cpuidle_lock acquired.
 */
static struct cpuidle_governor * __cpuidle_find_governor(const char *str)
{
	struct cpuidle_governor *gov;

	list_for_each_entry(gov, &cpuidle_governors, governor_list)
		if (!strnicmp(str, gov->name, CPUIDLE_NAME_LEN))
			return gov;

	return NULL;
}

/**
 * cpuidle_switch_governor - changes the governor
 * @gov: the new target governor
 *
 * NOTE: "gov" can be NULL to specify disabled
 * Must be called with cpuidle_lock acquired.
 */
int cpuidle_switch_governor(struct cpuidle_governor *gov)
{
	struct cpuidle_device *dev;

	if (gov == cpuidle_curr_governor)
		return 0;

	cpuidle_uninstall_idle_handler();

	if (cpuidle_curr_governor) {
		list_for_each_entry(dev, &cpuidle_detected_devices, device_list)
			cpuidle_disable_device(dev);
		module_put(cpuidle_curr_governor->owner);
	}

	cpuidle_curr_governor = gov;

	if (gov) {
		if (!try_module_get(cpuidle_curr_governor->owner))
			return -EINVAL;
		list_for_each_entry(dev, &cpuidle_detected_devices, device_list)
			cpuidle_enable_device(dev);
		cpuidle_install_idle_handler();
		printk(KERN_INFO "cpuidle: using governor %s\n", gov->name);
	}

	return 0;
}

/**
 * cpuidle_register_governor - registers a governor
 * @gov: the governor
 */
int cpuidle_register_governor(struct cpuidle_governor *gov)
{
	int ret = -EEXIST;

	if (!gov || !gov->select)
		return -EINVAL;

	if (cpuidle_disabled())
		return -ENODEV;

	mutex_lock(&cpuidle_lock);
	if (__cpuidle_find_governor(gov->name) == NULL) {
		ret = 0;
		list_add_tail(&gov->governor_list, &cpuidle_governors);
		if (!cpuidle_curr_governor ||
		    cpuidle_curr_governor->rating < gov->rating)
			cpuidle_switch_governor(gov);
	}
	mutex_unlock(&cpuidle_lock);

	return ret;
}

/**
 * cpuidle_replace_governor - find a replacement governor
 * @exclude_rating: the rating that will be skipped while looking for
 * new governor.
 */
static struct cpuidle_governor *cpuidle_replace_governor(int exclude_rating)
{
	struct cpuidle_governor *gov;
	struct cpuidle_governor *ret_gov = NULL;
	unsigned int max_rating = 0;

	list_for_each_entry(gov, &cpuidle_governors, governor_list) {
		if (gov->rating == exclude_rating)
			continue;
		if (gov->rating > max_rating) {
			max_rating = gov->rating;
			ret_gov = gov;
		}
	}

	return ret_gov;
}

/**
 * cpuidle_unregister_governor - unregisters a governor
 * @gov: the governor
 */
void cpuidle_unregister_governor(struct cpuidle_governor *gov)
{
	if (!gov)
		return;

	mutex_lock(&cpuidle_lock);
	if (gov == cpuidle_curr_governor) {
		struct cpuidle_governor *new_gov;
		new_gov = cpuidle_replace_governor(gov->rating);
		cpuidle_switch_governor(new_gov);
	}
	list_del(&gov->governor_list);
	mutex_unlock(&cpuidle_lock);
}

