#ifndef __NOUVEAU_OS_H__
#define __NOUVEAU_OS_H__

#include <beep/types.h>
#include <beep/slab.h>
#include <beep/mutex.h>
#include <beep/pci.h>
#include <beep/printk.h>
#include <beep/bitops.h>
#include <beep/firmware.h>
#include <beep/module.h>
#include <beep/i2c.h>
#include <beep/i2c-algo-bit.h>
#include <beep/delay.h>
#include <beep/io-mapping.h>
#include <beep/vmalloc.h>
#include <beep/acpi.h>
#include <beep/dmi.h>

#include <asm/unaligned.h>

static inline int
ffsll(u64 mask)
{
	int i;
	for (i = 0; i < 64; i++) {
		if (mask & (1ULL << i))
			return i + 1;
	}
	return 0;
}

#ifndef ioread32_native
#ifdef __BIG_ENDIAN
#define ioread16_native ioread16be
#define iowrite16_native iowrite16be
#define ioread32_native  ioread32be
#define iowrite32_native iowrite32be
#else /* def __BIG_ENDIAN */
#define ioread16_native ioread16
#define iowrite16_native iowrite16
#define ioread32_native  ioread32
#define iowrite32_native iowrite32
#endif /* def __BIG_ENDIAN else */
#endif /* !ioread32_native */

#endif
