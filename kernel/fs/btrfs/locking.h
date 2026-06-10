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
#ifndef __BTRFS_LOCKING_
#define __BTRFS_LOCKING_

#define BTRFS_WRITE_LOCK 1
#define BTRFS_READ_LOCK 2
#define BTRFS_WRITE_LOCK_BLOCKING 3
#define BTRFS_READ_LOCK_BLOCKING 4

void btrfs_tree_lock(struct extent_buffer *eb);
void btrfs_tree_unlock(struct extent_buffer *eb);
int btrfs_try_spin_lock(struct extent_buffer *eb);

void btrfs_tree_read_lock(struct extent_buffer *eb);
void btrfs_tree_read_unlock(struct extent_buffer *eb);
void btrfs_tree_read_unlock_blocking(struct extent_buffer *eb);
void btrfs_set_lock_blocking_rw(struct extent_buffer *eb, int rw);
void btrfs_clear_lock_blocking_rw(struct extent_buffer *eb, int rw);
void btrfs_assert_tree_locked(struct extent_buffer *eb);
int btrfs_try_tree_read_lock(struct extent_buffer *eb);
int btrfs_try_tree_write_lock(struct extent_buffer *eb);

static inline void btrfs_tree_unlock_rw(struct extent_buffer *eb, int rw)
{
	if (rw == BTRFS_WRITE_LOCK || rw == BTRFS_WRITE_LOCK_BLOCKING)
		btrfs_tree_unlock(eb);
	else if (rw == BTRFS_READ_LOCK_BLOCKING)
		btrfs_tree_read_unlock_blocking(eb);
	else if (rw == BTRFS_READ_LOCK)
		btrfs_tree_read_unlock(eb);
	else
		BUG();
}

static inline void btrfs_set_lock_blocking(struct extent_buffer *eb)
{
	btrfs_set_lock_blocking_rw(eb, BTRFS_WRITE_LOCK);
}

static inline void btrfs_clear_lock_blocking(struct extent_buffer *eb)
{
	btrfs_clear_lock_blocking_rw(eb, BTRFS_WRITE_LOCK_BLOCKING);
}
#endif
