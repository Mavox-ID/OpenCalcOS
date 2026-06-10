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

DEFINE_SPINLOCK(cpuidle_driver_lock);

static void __cpuidle_set_cpu_driver(struct cpuidle_driver *drv, int cpu);
static struct cpuidle_driver * __cpuidle_get_cpu_driver(int cpu);

static void __cpuidle_driver_init(struct cpuidle_driver *drv)
{
	drv->refcnt = 0;
}

static int __cpuidle_register_driver(struct cpuidle_driver *drv, int cpu)
{
	if (!drv || !drv->state_count)
		return -EINVAL;

	if (cpuidle_disabled())
		return -ENODEV;

	if (__cpuidle_get_cpu_driver(cpu))
		return -EBUSY;

	__cpuidle_driver_init(drv);

	__cpuidle_set_cpu_driver(drv, cpu);

	return 0;
}

static void __cpuidle_unregister_driver(struct cpuidle_driver *drv, int cpu)
{
	if (drv != __cpuidle_get_cpu_driver(cpu))
		return;

	if (!WARN_ON(drv->refcnt > 0))
		__cpuidle_set_cpu_driver(NULL, cpu);
}

#ifdef CONFIG_CPU_IDLE_MULTIPLE_DRIVERS

static DEFINE_PER_CPU(struct cpuidle_driver *, cpuidle_drivers);

static void __cpuidle_set_cpu_driver(struct cpuidle_driver *drv, int cpu)
{
	per_cpu(cpuidle_drivers, cpu) = drv;
}

static struct cpuidle_driver *__cpuidle_get_cpu_driver(int cpu)
{
	return per_cpu(cpuidle_drivers, cpu);
}

static void __cpuidle_unregister_all_cpu_driver(struct cpuidle_driver *drv)
{
	int cpu;
	for_each_present_cpu(cpu)
		__cpuidle_unregister_driver(drv, cpu);
}

static int __cpuidle_register_all_cpu_driver(struct cpuidle_driver *drv)
{
	int ret = 0;
	int i, cpu;

	for_each_present_cpu(cpu) {
		ret = __cpuidle_register_driver(drv, cpu);
		if (ret)
			break;
	}

	if (ret)
		for_each_present_cpu(i) {
			if (i == cpu)
				break;
			__cpuidle_unregister_driver(drv, i);
		}


	return ret;
}

int cpuidle_register_cpu_driver(struct cpuidle_driver *drv, int cpu)
{
	int ret;

	spin_lock(&cpuidle_driver_lock);
	ret = __cpuidle_register_driver(drv, cpu);
	spin_unlock(&cpuidle_driver_lock);

	return ret;
}

void cpuidle_unregister_cpu_driver(struct cpuidle_driver *drv, int cpu)
{
	spin_lock(&cpuidle_driver_lock);
	__cpuidle_unregister_driver(drv, cpu);
	spin_unlock(&cpuidle_driver_lock);
}

/**
 * cpuidle_register_driver - registers a driver
 * @drv: the driver
 */
int cpuidle_register_driver(struct cpuidle_driver *drv)
{
	int ret;

	spin_lock(&cpuidle_driver_lock);
	ret = __cpuidle_register_all_cpu_driver(drv);
	spin_unlock(&cpuidle_driver_lock);

	return ret;
}
EXPORT_SYMBOL_GPL(cpuidle_register_driver);

/**
 * cpuidle_unregister_driver - unregisters a driver
 * @drv: the driver
 */
void cpuidle_unregister_driver(struct cpuidle_driver *drv)
{
	spin_lock(&cpuidle_driver_lock);
	__cpuidle_unregister_all_cpu_driver(drv);
	spin_unlock(&cpuidle_driver_lock);
}
EXPORT_SYMBOL_GPL(cpuidle_unregister_driver);

#else

static struct cpuidle_driver *cpuidle_curr_driver;

static inline void __cpuidle_set_cpu_driver(struct cpuidle_driver *drv, int cpu)
{
	cpuidle_curr_driver = drv;
}

static inline struct cpuidle_driver *__cpuidle_get_cpu_driver(int cpu)
{
	return cpuidle_curr_driver;
}

/**
 * cpuidle_register_driver - registers a driver
 * @drv: the driver
 */
int cpuidle_register_driver(struct cpuidle_driver *drv)
{
	int ret, cpu;

	cpu = get_cpu();
	spin_lock(&cpuidle_driver_lock);
	ret = __cpuidle_register_driver(drv, cpu);
	spin_unlock(&cpuidle_driver_lock);
	put_cpu();

	return ret;
}
EXPORT_SYMBOL_GPL(cpuidle_register_driver);

/**
 * cpuidle_unregister_driver - unregisters a driver
 * @drv: the driver
 */
void cpuidle_unregister_driver(struct cpuidle_driver *drv)
{
	int cpu;

	cpu = get_cpu();
	spin_lock(&cpuidle_driver_lock);
	__cpuidle_unregister_driver(drv, cpu);
	spin_unlock(&cpuidle_driver_lock);
	put_cpu();
}
EXPORT_SYMBOL_GPL(cpuidle_unregister_driver);
#endif

/**
 * cpuidle_get_driver - return the current driver
 */
struct cpuidle_driver *cpuidle_get_driver(void)
{
	struct cpuidle_driver *drv;
	int cpu;

	cpu = get_cpu();
	drv = __cpuidle_get_cpu_driver(cpu);
	put_cpu();

	return drv;
}
EXPORT_SYMBOL_GPL(cpuidle_get_driver);

/**
 * cpuidle_get_cpu_driver - return the driver tied with a cpu
 */
struct cpuidle_driver *cpuidle_get_cpu_driver(struct cpuidle_device *dev)
{
	if (!dev)
		return NULL;

	return __cpuidle_get_cpu_driver(dev->cpu);
}
EXPORT_SYMBOL_GPL(cpuidle_get_cpu_driver);

struct cpuidle_driver *cpuidle_driver_ref(void)
{
	struct cpuidle_driver *drv;

	spin_lock(&cpuidle_driver_lock);

	drv = cpuidle_get_driver();
	drv->refcnt++;

	spin_unlock(&cpuidle_driver_lock);
	return drv;
}

void cpuidle_driver_unref(void)
{
	struct cpuidle_driver *drv = cpuidle_get_driver();

	spin_lock(&cpuidle_driver_lock);

	if (drv && !WARN_ON(drv->refcnt <= 0))
		drv->refcnt--;

	spin_unlock(&cpuidle_driver_lock);
}
