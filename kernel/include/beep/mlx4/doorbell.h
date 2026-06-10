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
#ifndef MLX4_DOORBELL_H
#define MLX4_DOORBELL_H

#include <beep/types.h>
#include <beep/io.h>

#define MLX4_SEND_DOORBELL    0x14
#define MLX4_CQ_DOORBELL      0x20

#if BITS_PER_LONG == 64
/*
 * Assume that we can just write a 64-bit doorbell atomically.  s390
 * actually doesn't have writeq() but S/390 systems don't even have
 * PCI so we won't worry about it.
 */

#define MLX4_DECLARE_DOORBELL_LOCK(name)
#define MLX4_INIT_DOORBELL_LOCK(ptr)    do { } while (0)
#define MLX4_GET_DOORBELL_LOCK(ptr)      (NULL)

static inline void mlx4_write64(__be32 val[2], void __iomem *dest,
				spinlock_t *doorbell_lock)
{
	__raw_writeq(*(u64 *) val, dest);
}

#else

/*
 * Just fall back to a spinlock to protect the doorbell if
 * BITS_PER_LONG is 32 -- there's no portable way to do atomic 64-bit
 * MMIO writes.
 */

#define MLX4_DECLARE_DOORBELL_LOCK(name) spinlock_t name;
#define MLX4_INIT_DOORBELL_LOCK(ptr)     spin_lock_init(ptr)
#define MLX4_GET_DOORBELL_LOCK(ptr)      (ptr)

static inline void mlx4_write64(__be32 val[2], void __iomem *dest,
				spinlock_t *doorbell_lock)
{
	unsigned long flags;

	spin_lock_irqsave(doorbell_lock, flags);
	__raw_writel((__force u32) val[0], dest);
	__raw_writel((__force u32) val[1], dest + 4);
	spin_unlock_irqrestore(doorbell_lock, flags);
}

#endif

#endif /* MLX4_DOORBELL_H */
