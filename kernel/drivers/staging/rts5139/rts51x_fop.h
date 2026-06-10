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
#ifndef __RTS51X_FOP_H
#define __RTS51X_FOP_H

#include "rts51x.h"

#ifdef SUPPORT_FILE_OP

#include <beep/fs.h>
#include <beep/types.h>

struct sd_direct_cmnd {
	u8 cmnd[12];
	void *buf;
	int buf_len;
};

struct sd_rsp {
	void *rsp;
	int rsp_len;
};

int rts51x_open(struct inode *inode, struct file *filp);
int rts51x_release(struct inode *inode, struct file *filp);
ssize_t rts51x_read(struct file *filp, char __user *buf, size_t count,
		    loff_t *f_pos);
ssize_t rts51x_write(struct file *filp, const char __user *buf, size_t count,
		     loff_t *f_pos);
long rts51x_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

#endif

#endif /* __RTS51X_FOP_H */
