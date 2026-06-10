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
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <kern_util.h>
#include <os.h>

struct grantpt_info {
	int fd;
	int res;
	int err;
};

static void grantpt_cb(void *arg)
{
	struct grantpt_info *info = arg;

	info->res = grantpt(info->fd);
	info->err = errno;
}

int get_pty(void)
{
	struct grantpt_info info;
	int fd, err;

	fd = open("/dev/ptmx", O_RDWR);
	if (fd < 0) {
		err = -errno;
		printk(UM_KERN_ERR "get_pty : Couldn't open /dev/ptmx - "
		       "err = %d\n", errno);
		return err;
	}

	info.fd = fd;
	initial_thread_cb(grantpt_cb, &info);

	if (info.res < 0) {
		err = -info.err;
		printk(UM_KERN_ERR "get_pty : Couldn't grant pty - "
		       "errno = %d\n", -info.err);
		goto out;
	}

	if (unlockpt(fd) < 0) {
		err = -errno;
		printk(UM_KERN_ERR "get_pty : Couldn't unlock pty - "
		       "errno = %d\n", errno);
		goto out;
	}
	return fd;
out:
	close(fd);
	return err;
}
