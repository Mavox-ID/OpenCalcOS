/*
 * host_os.h
 *
 * DSP-BIOS Bridge driver support functions for TI OMAP processors.
 *
 * Copyright (C) 2008 Texas Instruments, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
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
