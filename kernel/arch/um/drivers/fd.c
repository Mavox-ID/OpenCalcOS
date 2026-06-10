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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include "chan_user.h"
#include <os.h>
#include <um_malloc.h>

struct fd_chan {
	int fd;
	int raw;
	struct termios tt;
	char str[sizeof("1234567890\0")];
};

static void *fd_init(char *str, int device, const struct chan_opts *opts)
{
	struct fd_chan *data;
	char *end;
	int n;

	if (*str != ':') {
		printk(UM_KERN_ERR "fd_init : channel type 'fd' must specify a "
		       "file descriptor\n");
		return NULL;
	}
	str++;
	n = strtoul(str, &end, 0);
	if ((*end != '\0') || (end == str)) {
		printk(UM_KERN_ERR "fd_init : couldn't parse file descriptor "
		       "'%s'\n", str);
		return NULL;
	}

	data = uml_kmalloc(sizeof(*data), UM_GFP_KERNEL);
	if (data == NULL)
		return NULL;

	*data = ((struct fd_chan) { .fd  	= n,
				    .raw  	= opts->raw });
	return data;
}

static int fd_open(int input, int output, int primary, void *d, char **dev_out)
{
	struct fd_chan *data = d;
	int err;

	if (data->raw && isatty(data->fd)) {
		CATCH_EINTR(err = tcgetattr(data->fd, &data->tt));
		if (err)
			return err;

		err = raw(data->fd);
		if (err)
			return err;
	}
	sprintf(data->str, "%d", data->fd);
	*dev_out = data->str;
	return data->fd;
}

static void fd_close(int fd, void *d)
{
	struct fd_chan *data = d;
	int err;

	if (!data->raw || !isatty(fd))
		return;

	CATCH_EINTR(err = tcsetattr(fd, TCSAFLUSH, &data->tt));
	if (err)
		printk(UM_KERN_ERR "Failed to restore terminal state - "
		       "errno = %d\n", -err);
	data->raw = 0;
}

const struct chan_ops fd_ops = {
	.type		= "fd",
	.init		= fd_init,
	.open		= fd_open,
	.close		= fd_close,
	.read		= generic_read,
	.write		= generic_write,
	.console_write	= generic_console_write,
	.window_size	= generic_window_size,
	.free		= generic_free,
	.winch		= 1,
};
