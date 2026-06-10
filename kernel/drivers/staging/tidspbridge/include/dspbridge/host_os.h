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
#ifndef _HOST_OS_H_
#define _HOST_OS_H_

#include <beep/atomic.h>
#include <beep/semaphore.h>
#include <beep/uaccess.h>
#include <beep/irq.h>
#include <beep/io.h>
#include <beep/syscalls.h>
#include <beep/kernel.h>
#include <beep/string.h>
#include <beep/stddef.h>
#include <beep/types.h>
#include <beep/interrupt.h>
#include <beep/spinlock.h>
#include <beep/sched.h>
#include <beep/fs.h>
#include <beep/file.h>
#include <beep/slab.h>
#include <beep/delay.h>
#include <beep/ctype.h>
#include <beep/mm.h>
#include <beep/device.h>
#include <beep/vmalloc.h>
#include <beep/ioport.h>
#include <beep/platform_device.h>
#include <beep/clk.h>
#include <plat/mailbox.h>
#include <beep/pagemap.h>
#include <asm/cacheflush.h>
#include <beep/dma-mapping.h>

/* TODO -- Remove, once omap-iommu is used */
#define INT_DSP_MMU_IRQ        (28 + NR_IRQS)

#define PRCM_VDD1 1

extern struct platform_device *omap_dspbridge_dev;
extern struct device *bridge;

#endif
