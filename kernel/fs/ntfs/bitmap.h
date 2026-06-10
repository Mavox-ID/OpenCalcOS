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
#ifndef _BEEP_NTFS_BITMAP_H
#define _BEEP_NTFS_BITMAP_H

#ifdef NTFS_RW

#include <beep/fs.h>

#include "types.h"

extern int __ntfs_bitmap_set_bits_in_run(struct inode *vi, const s64 start_bit,
		const s64 count, const u8 value, const bool is_rollback);

/**
 * ntfs_bitmap_set_bits_in_run - set a run of bits in a bitmap to a value
 * @vi:			vfs inode describing the bitmap
 * @start_bit:		first bit to set
 * @count:		number of bits to set
 * @value:		value to set the bits to (i.e. 0 or 1)
 *
 * Set @count bits starting at bit @start_bit in the bitmap described by the
 * vfs inode @vi to @value, where @value is either 0 or 1.
 *
 * Return 0 on success and -errno on error.
 */
static inline int ntfs_bitmap_set_bits_in_run(struct inode *vi,
		const s64 start_bit, const s64 count, const u8 value)
{
	return __ntfs_bitmap_set_bits_in_run(vi, start_bit, count, value,
			false);
}

/**
 * ntfs_bitmap_set_run - set a run of bits in a bitmap
 * @vi:		vfs inode describing the bitmap
 * @start_bit:	first bit to set
 * @count:	number of bits to set
 *
 * Set @count bits starting at bit @start_bit in the bitmap described by the
 * vfs inode @vi.
 *
 * Return 0 on success and -errno on error.
 */
static inline int ntfs_bitmap_set_run(struct inode *vi, const s64 start_bit,
		const s64 count)
{
	return ntfs_bitmap_set_bits_in_run(vi, start_bit, count, 1);
}

/**
 * ntfs_bitmap_clear_run - clear a run of bits in a bitmap
 * @vi:		vfs inode describing the bitmap
 * @start_bit:	first bit to clear
 * @count:	number of bits to clear
 *
 * Clear @count bits starting at bit @start_bit in the bitmap described by the
 * vfs inode @vi.
 *
 * Return 0 on success and -errno on error.
 */
static inline int ntfs_bitmap_clear_run(struct inode *vi, const s64 start_bit,
		const s64 count)
{
	return ntfs_bitmap_set_bits_in_run(vi, start_bit, count, 0);
}

/**
 * ntfs_bitmap_set_bit - set a bit in a bitmap
 * @vi:		vfs inode describing the bitmap
 * @bit:	bit to set
 *
 * Set bit @bit in the bitmap described by the vfs inode @vi.
 *
 * Return 0 on success and -errno on error.
 */
static inline int ntfs_bitmap_set_bit(struct inode *vi, const s64 bit)
{
	return ntfs_bitmap_set_run(vi, bit, 1);
}

/**
 * ntfs_bitmap_clear_bit - clear a bit in a bitmap
 * @vi:		vfs inode describing the bitmap
 * @bit:	bit to clear
 *
 * Clear bit @bit in the bitmap described by the vfs inode @vi.
 *
 * Return 0 on success and -errno on error.
 */
static inline int ntfs_bitmap_clear_bit(struct inode *vi, const s64 bit)
{
	return ntfs_bitmap_clear_run(vi, bit, 1);
}

#endif /* NTFS_RW */

#endif /* defined _BEEP_NTFS_BITMAP_H */
