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
#ifndef __ASM_ARCH_TICK_H
#define __ASM_ARCH_TICK_H __FILE__

/* note, the timer interrutps turn up in 2 places, the vic and then
 * the timer block. We take the VIC as the base at the moment.
 */
static inline u32 s3c24xx_ostimer_pending(void)
{
	u32 pend = __raw_readl(VA_VIC0 + VIC_RAW_STATUS);
	return pend & 1 << (IRQ_TIMER4_VIC - S3C64XX_IRQ_VIC0(0));
}

#define TICK_MAX	(0xffffffff)

#endif /* __ASM_ARCH_6400_TICK_H */
