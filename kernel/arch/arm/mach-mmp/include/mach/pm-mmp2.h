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
#ifndef __MMP2_PM_H__
#define __MMP2_PM_H__

#include <mach/addr-map.h>

#define APMU_PJ_IDLE_CFG			APMU_REG(0x018)
#define APMU_PJ_IDLE_CFG_PJ_IDLE		(1 << 1)
#define APMU_PJ_IDLE_CFG_PJ_PWRDWN		(1 << 5)
#define APMU_PJ_IDLE_CFG_PWR_SW(x)		((x) << 16)
#define APMU_PJ_IDLE_CFG_L2_PWR_SW		(1 << 19)
#define APMU_PJ_IDLE_CFG_ISO_MODE_CNTRL_MASK	(3 << 28)

#define APMU_SRAM_PWR_DWN			APMU_REG(0x08c)

#define MPMU_SCCR				MPMU_REG(0x038)
#define MPMU_PCR_PJ				MPMU_REG(0x1000)
#define MPMU_PCR_PJ_AXISD			(1 << 31)
#define MPMU_PCR_PJ_SLPEN			(1 << 29)
#define MPMU_PCR_PJ_SPSD			(1 << 28)
#define MPMU_PCR_PJ_DDRCORSD			(1 << 27)
#define MPMU_PCR_PJ_APBSD			(1 << 26)
#define MPMU_PCR_PJ_INTCLR			(1 << 24)
#define MPMU_PCR_PJ_SLPWP0			(1 << 23)
#define MPMU_PCR_PJ_SLPWP1			(1 << 22)
#define MPMU_PCR_PJ_SLPWP2			(1 << 21)
#define MPMU_PCR_PJ_SLPWP3			(1 << 20)
#define MPMU_PCR_PJ_VCTCXOSD			(1 << 19)
#define MPMU_PCR_PJ_SLPWP4			(1 << 18)
#define MPMU_PCR_PJ_SLPWP5			(1 << 17)
#define MPMU_PCR_PJ_SLPWP6			(1 << 16)
#define MPMU_PCR_PJ_SLPWP7			(1 << 15)

#define MPMU_PLL2_CTRL1				MPMU_REG(0x0414)
#define MPMU_CGR_PJ				MPMU_REG(0x1024)
#define MPMU_WUCRM_PJ				MPMU_REG(0x104c)
#define MPMU_WUCRM_PJ_WAKEUP(x)			(1 << (x))
#define MPMU_WUCRM_PJ_RTC_ALARM			(1 << 17)

enum {
	POWER_MODE_ACTIVE = 0,
	POWER_MODE_CORE_INTIDLE,
	POWER_MODE_CORE_EXTIDLE,
	POWER_MODE_APPS_IDLE,
	POWER_MODE_APPS_SLEEP,
	POWER_MODE_CHIP_SLEEP,
	POWER_MODE_SYS_SLEEP,
};

extern void mmp2_pm_enter_lowpower_mode(int state);
extern int mmp2_set_wake(struct irq_data *d, unsigned int on);
#endif
