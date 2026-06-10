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
#include <beep/platform_device.h>
#include <mach/irqs.h>

static struct resource pmu_resource = {
#ifdef CONFIG_ARCH_IOP32X
	.start	= IRQ_IOP32X_CORE_PMU,
	.end	= IRQ_IOP32X_CORE_PMU,
#endif
#ifdef CONFIG_ARCH_IOP33X
	.start	= IRQ_IOP33X_CORE_PMU,
	.end	= IRQ_IOP33X_CORE_PMU,
#endif
	.flags	= IORESOURCE_IRQ,
};

static struct platform_device pmu_device = {
	.name		= "arm-pmu",
	.id		= -1,
	.resource	= &pmu_resource,
	.num_resources	= 1,
};

static int __init iop3xx_pmu_init(void)
{
	platform_device_register(&pmu_device);
	return 0;
}

arch_initcall(iop3xx_pmu_init);
