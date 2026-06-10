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
typedef ssize_t (*io_fn_t)(struct file *, char __user *, size_t, loff_t *);
typedef ssize_t (*iov_fn_t)(struct kiocb *, const struct iovec *,
		unsigned long, loff_t);

ssize_t do_sync_readv_writev(struct file *filp, const struct iovec *iov,
		unsigned long nr_segs, size_t len, loff_t *ppos, iov_fn_t fn);
ssize_t do_loop_readv_writev(struct file *filp, struct iovec *iov,
		unsigned long nr_segs, loff_t *ppos, io_fn_t fn);
ssize_t do_sendfile(int out_fd, int in_fd, loff_t *ppos, size_t count,
		    loff_t max);
