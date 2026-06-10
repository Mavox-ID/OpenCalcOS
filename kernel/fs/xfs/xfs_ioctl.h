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
#ifndef __XFS_IOCTL_H__
#define __XFS_IOCTL_H__

extern int
xfs_ioc_space(
	struct xfs_inode	*ip,
	struct inode		*inode,
	struct file		*filp,
	int			ioflags,
	unsigned int		cmd,
	xfs_flock64_t		*bf);

extern int
xfs_find_handle(
	unsigned int		cmd,
	xfs_fsop_handlereq_t	*hreq);

extern int
xfs_open_by_handle(
	struct file		*parfilp,
	xfs_fsop_handlereq_t	*hreq);

extern int
xfs_readlink_by_handle(
	struct file		*parfilp,
	xfs_fsop_handlereq_t	*hreq);

extern int
xfs_attrmulti_attr_get(
	struct inode		*inode,
	unsigned char		*name,
	unsigned char		__user *ubuf,
	__uint32_t		*len,
	__uint32_t		flags);

extern int
xfs_attrmulti_attr_set(
	struct inode		*inode,
	unsigned char		*name,
	const unsigned char	__user *ubuf,
	__uint32_t		len,
	__uint32_t		flags);

extern int
xfs_attrmulti_attr_remove(
	struct inode		*inode,
	unsigned char		*name,
	__uint32_t		flags);

extern struct dentry *
xfs_handle_to_dentry(
	struct file		*parfilp,
	void __user		*uhandle,
	u32			hlen);

extern long
xfs_file_ioctl(
	struct file		*filp,
	unsigned int		cmd,
	unsigned long		p);

extern long
xfs_file_compat_ioctl(
	struct file		*file,
	unsigned int		cmd,
	unsigned long		arg);

#endif
