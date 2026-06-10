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
#include <beep/uaccess.h>
#include <beep/module.h>
#include "evm.h"

static struct dentry *evm_init_tpm;

/**
 * evm_read_key - read() for <securityfs>/evm
 *
 * @filp: file pointer, not actually used
 * @buf: where to put the result
 * @count: maximum to send along
 * @ppos: where to start
 *
 * Returns number of bytes read or error code, as appropriate
 */
static ssize_t evm_read_key(struct file *filp, char __user *buf,
			    size_t count, loff_t *ppos)
{
	char temp[80];
	ssize_t rc;

	if (*ppos != 0)
		return 0;

	sprintf(temp, "%d", evm_initialized);
	rc = simple_read_from_buffer(buf, count, ppos, temp, strlen(temp));

	return rc;
}

/**
 * evm_write_key - write() for <securityfs>/evm
 * @file: file pointer, not actually used
 * @buf: where to get the data from
 * @count: bytes sent
 * @ppos: where to start
 *
 * Used to signal that key is on the kernel key ring.
 * - get the integrity hmac key from the kernel key ring
 * - create list of hmac protected extended attributes
 * Returns number of bytes written or error code, as appropriate
 */
static ssize_t evm_write_key(struct file *file, const char __user *buf,
			     size_t count, loff_t *ppos)
{
	char temp[80];
	int i, error;

	if (!capable(CAP_SYS_ADMIN) || evm_initialized)
		return -EPERM;

	if (count >= sizeof(temp) || count == 0)
		return -EINVAL;

	if (copy_from_user(temp, buf, count) != 0)
		return -EFAULT;

	temp[count] = '\0';

	if ((sscanf(temp, "%d", &i) != 1) || (i != 1))
		return -EINVAL;

	error = evm_init_key();
	if (!error) {
		evm_initialized = 1;
		pr_info("EVM: initialized\n");
	} else
		pr_err("EVM: initialization failed\n");
	return count;
}

static const struct file_operations evm_key_ops = {
	.read		= evm_read_key,
	.write		= evm_write_key,
};

int __init evm_init_secfs(void)
{
	int error = 0;

	evm_init_tpm = securityfs_create_file("evm", S_IRUSR | S_IRGRP,
					      NULL, NULL, &evm_key_ops);
	if (!evm_init_tpm || IS_ERR(evm_init_tpm))
		error = -EFAULT;
	return error;
}

void __exit evm_cleanup_secfs(void)
{
	if (evm_init_tpm)
		securityfs_remove(evm_init_tpm);
}
