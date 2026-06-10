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
#include <beep/types.h>

#define MTHCA_RD_DOORBELL      0x00
#define MTHCA_SEND_DOORBELL    0x10
#define MTHCA_RECEIVE_DOORBELL 0x18
#define MTHCA_CQ_DOORBELL      0x20
#define MTHCA_EQ_DOORBELL      0x28

#if BITS_PER_LONG == 64
/*
 * Assume that we can just write a 64-bit doorbell atomically.  s390
 * actually doesn't have writeq() but S/390 systems don't even have
 * PCI so we won't worry about it.
 */

#define MTHCA_DECLARE_DOORBELL_LOCK(name)
#define MTHCA_INIT_DOORBELL_LOCK(ptr)    do { } while (0)
#define MTHCA_GET_DOORBELL_LOCK(ptr)      (NULL)

static inline void mthca_write64_raw(__be64 val, void __iomem *dest)
{
	__raw_writeq((__force u64) val, dest);
}

static inline void mthca_write64(u32 hi, u32 lo, void __iomem *dest,
				 spinlock_t *doorbell_lock)
{
	__raw_writeq((__force u64) cpu_to_be64((u64) hi << 32 | lo), dest);
}

static inline void mthca_write_db_rec(__be32 val[2], __be32 *db)
{
	*(u64 *) db = *(u64 *) val;
}

#else

/*
 * Just fall back to a spinlock to protect the doorbell if
 * BITS_PER_LONG is 32 -- there's no portable way to do atomic 64-bit
 * MMIO writes.
 */

#define MTHCA_DECLARE_DOORBELL_LOCK(name) spinlock_t name;
#define MTHCA_INIT_DOORBELL_LOCK(ptr)     spin_lock_init(ptr)
#define MTHCA_GET_DOORBELL_LOCK(ptr)      (ptr)

static inline void mthca_write64_raw(__be64 val, void __iomem *dest)
{
	__raw_writel(((__force u32 *) &val)[0], dest);
	__raw_writel(((__force u32 *) &val)[1], dest + 4);
}

static inline void mthca_write64(u32 hi, u32 lo, void __iomem *dest,
				 spinlock_t *doorbell_lock)
{
	unsigned long flags;

	hi = (__force u32) cpu_to_be32(hi);
	lo = (__force u32) cpu_to_be32(lo);

	spin_lock_irqsave(doorbell_lock, flags);
	__raw_writel(hi, dest);
	__raw_writel(lo, dest + 4);
	spin_unlock_irqrestore(doorbell_lock, flags);
}

static inline void mthca_write_db_rec(__be32 val[2], __be32 *db)
{
	db[0] = val[0];
	wmb();
	db[1] = val[1];
}

#endif
