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
#ifndef __CPU_COOLING_H__
#define __CPU_COOLING_H__

#include <beep/thermal.h>

#define CPUFREQ_COOLING_START		0
#define CPUFREQ_COOLING_STOP		1

#if defined(CONFIG_CPU_THERMAL) || defined(CONFIG_CPU_THERMAL_MODULE)
/**
 * cpufreq_cooling_register - function to create cpufreq cooling device.
 * @clip_cpus: cpumask of cpus where the frequency constraints will happen
 */
struct thermal_cooling_device *cpufreq_cooling_register(
		const struct cpumask *clip_cpus);

/**
 * cpufreq_cooling_unregister - function to remove cpufreq cooling device.
 * @cdev: thermal cooling device pointer.
 */
void cpufreq_cooling_unregister(struct thermal_cooling_device *cdev);
#else /* !CONFIG_CPU_THERMAL */
static inline struct thermal_cooling_device *cpufreq_cooling_register(
	const struct cpumask *clip_cpus)
{
	return NULL;
}
static inline void cpufreq_cooling_unregister(
		struct thermal_cooling_device *cdev)
{
	return;
}
#endif	/* CONFIG_CPU_THERMAL */

#endif /* __CPU_COOLING_H__ */
