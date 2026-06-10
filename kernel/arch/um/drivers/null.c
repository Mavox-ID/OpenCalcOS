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
#include <stddef.h>
#include <errno.h>
#include <fcntl.h>
#include "chan_user.h"
#include <os.h>

/* This address is used only as a unique identifier */
static int null_chan;

static void *null_init(char *str, int device, const struct chan_opts *opts)
{
	return &null_chan;
}

static int null_open(int input, int output, int primary, void *d,
		     char **dev_out)
{
	int fd;

	*dev_out = NULL;

	fd = open(DEV_NULL, O_RDWR);
	return (fd < 0) ? -errno : fd;
}

static int null_read(int fd, char *c_out, void *unused)
{
	return -ENODEV;
}

static void null_free(void *data)
{
}

const struct chan_ops null_ops = {
	.type		= "null",
	.init		= null_init,
	.open		= null_open,
	.close		= generic_close,
	.read		= null_read,
	.write		= generic_write,
	.console_write	= generic_console_write,
	.window_size	= generic_window_size,
	.free		= null_free,
	.winch		= 0,
};
