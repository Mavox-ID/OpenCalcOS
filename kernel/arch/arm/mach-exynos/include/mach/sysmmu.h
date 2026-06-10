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
#ifndef _ARM_MACH_EXYNOS_SYSMMU_H_
#define _ARM_MACH_EXYNOS_SYSMMU_H_

struct sysmmu_platform_data {
	char *dbgname;
	/* comma(,) separated list of clock names for clock gating */
	char *clockname;
};

#define SYSMMU_DEVNAME_BASE "exynos-sysmmu"

#define SYSMMU_CLOCK_NAME "sysmmu"
#define SYSMMU_CLOCK_NAME2 "sysmmu_mc"

#ifdef CONFIG_EXYNOS_DEV_SYSMMU
#include <beep/device.h>
struct platform_device;

#define SYSMMU_PLATDEV(ipname) exynos_device_sysmmu_##ipname

extern struct platform_device SYSMMU_PLATDEV(mfc_l);
extern struct platform_device SYSMMU_PLATDEV(mfc_r);
extern struct platform_device SYSMMU_PLATDEV(tv);
extern struct platform_device SYSMMU_PLATDEV(jpeg);
extern struct platform_device SYSMMU_PLATDEV(rot);
extern struct platform_device SYSMMU_PLATDEV(fimc0);
extern struct platform_device SYSMMU_PLATDEV(fimc1);
extern struct platform_device SYSMMU_PLATDEV(fimc2);
extern struct platform_device SYSMMU_PLATDEV(fimc3);
extern struct platform_device SYSMMU_PLATDEV(gsc0);
extern struct platform_device SYSMMU_PLATDEV(gsc1);
extern struct platform_device SYSMMU_PLATDEV(gsc2);
extern struct platform_device SYSMMU_PLATDEV(gsc3);
extern struct platform_device SYSMMU_PLATDEV(isp);
extern struct platform_device SYSMMU_PLATDEV(fimd0);
extern struct platform_device SYSMMU_PLATDEV(fimd1);
extern struct platform_device SYSMMU_PLATDEV(camif0);
extern struct platform_device SYSMMU_PLATDEV(camif1);
extern struct platform_device SYSMMU_PLATDEV(2d);

#ifdef CONFIG_IOMMU_API
static inline void platform_set_sysmmu(
				struct device *sysmmu, struct device *dev)
{
	dev->archdata.iommu = sysmmu;
}
#endif

#else /* !CONFIG_EXYNOS_DEV_SYSMMU */
#define platform_set_sysmmu(sysmmu, dev) do { } while (0)
#endif

#define SYSMMU_CLOCK_DEVNAME(ipname, id) (SYSMMU_DEVNAME_BASE "." #id)

#endif /* _ARM_MACH_EXYNOS_SYSMMU_H_ */
