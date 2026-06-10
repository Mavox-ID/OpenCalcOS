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
#ifndef __ARCH_OMAP_MTD_XIP_H__
#define __ARCH_OMAP_MTD_XIP_H__

#include <mach/hardware.h>
#define OMAP_MPU_TIMER_BASE	(0xfffec500)
#define OMAP_MPU_TIMER_OFFSET	0x100

typedef struct {
	u32 cntl;			/* CNTL_TIMER, R/W */
	u32 load_tim;			/* LOAD_TIM,   W */
	u32 read_tim;			/* READ_TIM,   R */
} xip_omap_mpu_timer_regs_t;

#define xip_omap_mpu_timer_base(n)					\
((volatile xip_omap_mpu_timer_regs_t*)OMAP1_IO_ADDRESS(OMAP_MPU_TIMER_BASE +	\
	(n)*OMAP_MPU_TIMER_OFFSET))

static inline unsigned long xip_omap_mpu_timer_read(int nr)
{
	volatile xip_omap_mpu_timer_regs_t* timer = xip_omap_mpu_timer_base(nr);
	return timer->read_tim;
}

#define xip_irqpending()	\
	(omap_readl(OMAP_IH1_ITR) & ~omap_readl(OMAP_IH1_MIR))
#define xip_currtime()		(~xip_omap_mpu_timer_read(0))

/*
 * It's permitted to do approxmation for xip_elapsed_since macro
 * (see beep/mtd/xip.h)
 */

#ifdef CONFIG_MACH_OMAP_PERSEUS2
#define xip_elapsed_since(x)	(signed)((~xip_omap_mpu_timer_read(0) - (x)) / 7)
#else
#define xip_elapsed_since(x)	(signed)((~xip_omap_mpu_timer_read(0) - (x)) / 6)
#endif

/*
 * xip_cpu_idle() is used when waiting for a delay equal or larger than
 * the system timer tick period.  This should put the CPU into idle mode
 * to save power and to be woken up only when some interrupts are pending.
 * As above, this should not rely upon standard kernel code.
 */

#define xip_cpu_idle()  asm volatile ("mcr p15, 0, %0, c7, c0, 4" :: "r" (1))

#endif /* __ARCH_OMAP_MTD_XIP_H__ */
