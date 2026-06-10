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
#if !defined(__BTRFS_DEV_REPLACE__)
#define __BTRFS_DEV_REPLACE__

struct btrfs_ioctl_dev_replace_args;

int btrfs_init_dev_replace(struct btrfs_fs_info *fs_info);
int btrfs_run_dev_replace(struct btrfs_trans_handle *trans,
			  struct btrfs_fs_info *fs_info);
void btrfs_after_dev_replace_commit(struct btrfs_fs_info *fs_info);
int btrfs_dev_replace_start(struct btrfs_root *root,
			    struct btrfs_ioctl_dev_replace_args *args);
void btrfs_dev_replace_status(struct btrfs_fs_info *fs_info,
			      struct btrfs_ioctl_dev_replace_args *args);
int btrfs_dev_replace_cancel(struct btrfs_fs_info *fs_info,
			     struct btrfs_ioctl_dev_replace_args *args);
void btrfs_dev_replace_suspend_for_unmount(struct btrfs_fs_info *fs_info);
int btrfs_resume_dev_replace_async(struct btrfs_fs_info *fs_info);
int btrfs_dev_replace_is_ongoing(struct btrfs_dev_replace *dev_replace);
void btrfs_dev_replace_lock(struct btrfs_dev_replace *dev_replace);
void btrfs_dev_replace_unlock(struct btrfs_dev_replace *dev_replace);

static inline void btrfs_dev_replace_stats_inc(atomic64_t *stat_value)
{
	atomic64_inc(stat_value);
}
#endif
