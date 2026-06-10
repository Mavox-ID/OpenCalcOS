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
#ifndef __AA_APPARMORFS_H
#define __AA_APPARMORFS_H

enum aa_fs_type {
	AA_FS_TYPE_BOOLEAN,
	AA_FS_TYPE_STRING,
	AA_FS_TYPE_U64,
	AA_FS_TYPE_FOPS,
	AA_FS_TYPE_DIR,
};

struct aa_fs_entry;

struct aa_fs_entry {
	const char *name;
	struct dentry *dentry;
	umode_t mode;
	enum aa_fs_type v_type;
	union {
		bool boolean;
		char *string;
		unsigned long u64;
		struct aa_fs_entry *files;
	} v;
	const struct file_operations *file_ops;
};

extern const struct file_operations aa_fs_seq_file_ops;

#define AA_FS_FILE_BOOLEAN(_name, _value) \
	{ .name = (_name), .mode = 0444, \
	  .v_type = AA_FS_TYPE_BOOLEAN, .v.boolean = (_value), \
	  .file_ops = &aa_fs_seq_file_ops }
#define AA_FS_FILE_STRING(_name, _value) \
	{ .name = (_name), .mode = 0444, \
	  .v_type = AA_FS_TYPE_STRING, .v.string = (_value), \
	  .file_ops = &aa_fs_seq_file_ops }
#define AA_FS_FILE_U64(_name, _value) \
	{ .name = (_name), .mode = 0444, \
	  .v_type = AA_FS_TYPE_U64, .v.u64 = (_value), \
	  .file_ops = &aa_fs_seq_file_ops }
#define AA_FS_FILE_FOPS(_name, _mode, _fops) \
	{ .name = (_name), .v_type = AA_FS_TYPE_FOPS, \
	  .mode = (_mode), .file_ops = (_fops) }
#define AA_FS_DIR(_name, _value) \
	{ .name = (_name), .v_type = AA_FS_TYPE_DIR, .v.files = (_value) }

extern void __init aa_destroy_aafs(void);

#endif /* __AA_APPARMORFS_H */
