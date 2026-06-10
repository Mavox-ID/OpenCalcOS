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
#if !defined(__BTRFS_CHECK_INTEGRITY__)
#define __BTRFS_CHECK_INTEGRITY__

#ifdef CONFIG_BTRFS_FS_CHECK_INTEGRITY
int btrfsic_submit_bh(int rw, struct buffer_head *bh);
void btrfsic_submit_bio(int rw, struct bio *bio);
#else
#define btrfsic_submit_bh submit_bh
#define btrfsic_submit_bio submit_bio
#endif

int btrfsic_mount(struct btrfs_root *root,
		  struct btrfs_fs_devices *fs_devices,
		  int including_extent_data, u32 print_mask);
void btrfsic_unmount(struct btrfs_root *root,
		     struct btrfs_fs_devices *fs_devices);

#endif
