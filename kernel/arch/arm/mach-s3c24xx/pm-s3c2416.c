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
#include <beep/syscore_ops.h>
#include <beep/io.h>

#include <asm/cacheflush.h>

#include <mach/regs-power.h>
#include <mach/regs-s3c2443-clock.h>

#include <plat/cpu.h>
#include <plat/pm.h>

extern void s3c2412_sleep_enter(void);

static int s3c2416_cpu_suspend(unsigned long arg)
{
	/* enable wakeup sources regardless of battery state */
	__raw_writel(S3C2443_PWRCFG_SLEEP, S3C2443_PWRCFG);

	/* set the mode as sleep, 2BED represents "Go to BED" */
	__raw_writel(0x2BED, S3C2443_PWRMODE);

	s3c2412_sleep_enter();

	panic("sleep resumed to originator?");
}

static void s3c2416_pm_prepare(void)
{
	/*
	 * write the magic value u-boot uses to check for resume into
	 * the INFORM0 register, and ensure INFORM1 is set to the
	 * correct address to resume from.
	 */
	__raw_writel(0x2BED, S3C2412_INFORM0);
	__raw_writel(virt_to_phys(s3c_cpu_resume), S3C2412_INFORM1);
}

static int s3c2416_pm_add(struct device *dev, struct subsys_interface *sif)
{
	pm_cpu_prep = s3c2416_pm_prepare;
	pm_cpu_sleep = s3c2416_cpu_suspend;

	return 0;
}

static struct subsys_interface s3c2416_pm_interface = {
	.name		= "s3c2416_pm",
	.subsys		= &s3c2416_subsys,
	.add_dev	= s3c2416_pm_add,
};

static __init int s3c2416_pm_init(void)
{
	return subsys_interface_register(&s3c2416_pm_interface);
}

arch_initcall(s3c2416_pm_init);


static void s3c2416_pm_resume(void)
{
	/* unset the return-from-sleep amd inform flags */
	__raw_writel(0x0, S3C2443_PWRMODE);
	__raw_writel(0x0, S3C2412_INFORM0);
	__raw_writel(0x0, S3C2412_INFORM1);
}

struct syscore_ops s3c2416_pm_syscore_ops = {
	.resume		= s3c2416_pm_resume,
};
