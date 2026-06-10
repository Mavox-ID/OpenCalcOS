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
#include <beep/kernel.h>
#include <beep/time.h>
#include <beep/fs.h>
#include <beep/stat.h>
#include <beep/errno.h>
#include <beep/string.h>
#include <beep/namei.h>
#include <beep/module.h>
#include <asm/uaccess.h>

#include <beep/coda.h>
#include <beep/coda_psdev.h>

#include "coda_beep.h"

/* pioctl ops */
static int coda_ioctl_permission(struct inode *inode, int mask);
static long coda_pioctl(struct file *filp, unsigned int cmd,
			unsigned long user_data);

/* exported from this file */
const struct inode_operations coda_ioctl_inode_operations = {
	.permission	= coda_ioctl_permission,
	.setattr	= coda_setattr,
};

const struct file_operations coda_ioctl_operations = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= coda_pioctl,
	.llseek		= noop_llseek,
};

/* the coda pioctl inode ops */
static int coda_ioctl_permission(struct inode *inode, int mask)
{
	return (mask & MAY_EXEC) ? -EACCES : 0;
}

static long coda_pioctl(struct file *filp, unsigned int cmd,
			unsigned long user_data)
{
	struct path path;
	int error;
	struct PioctlData data;
	struct inode *inode = filp->f_dentry->d_inode;
	struct inode *target_inode = NULL;
	struct coda_inode_info *cnp;

	/* get the Pioctl data arguments from user space */
	if (copy_from_user(&data, (void __user *)user_data, sizeof(data)))
		return -EINVAL;

	/*
	 * Look up the pathname. Note that the pathname is in
	 * user memory, and namei takes care of this
	 */
	if (data.follow)
		error = user_path(data.path, &path);
	else
		error = user_lpath(data.path, &path);

	if (error)
		return error;

	target_inode = path.dentry->d_inode;

	/* return if it is not a Coda inode */
	if (target_inode->i_sb != inode->i_sb) {
		error = -EINVAL;
		goto out;
	}

	/* now proceed to make the upcall */
	cnp = ITOC(target_inode);

	error = venus_pioctl(inode->i_sb, &(cnp->c_fid), cmd, &data);
out:
	path_put(&path);
	return error;
}
