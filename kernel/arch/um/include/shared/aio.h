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
#ifndef AIO_H__
#define AIO_H__

enum aio_type { AIO_READ, AIO_WRITE, AIO_MMAP };

struct aio_thread_reply {
	void *data;
	int err;
};

struct aio_context {
	int reply_fd;
	struct aio_context *next;
};

#define INIT_AIO_CONTEXT { .reply_fd	= -1, \
			   .next	= NULL }

extern int submit_aio(enum aio_type type, int fd, char *buf, int len,
		      unsigned long long offset, int reply_fd,
                      struct aio_context *aio);

#endif
