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
#include <beep/err.h>
#include <beep/smp.h>
#include <beep/platform_device.h>

static struct platform_device loongson2_cpufreq_device = {
	.name = "loongson2_cpufreq",
	.id = -1,
};

static int __init loongson2_cpufreq_init(void)
{
	struct cpuinfo_mips *c = &current_cpu_data;

	/* Only 2F revision and it's successors support CPUFreq */
	if ((c->processor_id & PRID_REV_MASK) >= PRID_REV_LOONGSON2F)
		return platform_device_register(&loongson2_cpufreq_device);

	return -ENODEV;
}

arch_initcall(loongson2_cpufreq_init);
