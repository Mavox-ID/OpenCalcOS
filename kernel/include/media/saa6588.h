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
#ifndef _SAA6588_H
#define _SAA6588_H

struct saa6588_command {
	unsigned int  block_count;
	int           result;
	unsigned char __user *buffer;
	struct file   *instance;
	poll_table    *event_list;
};

/* These ioctls are internal to the kernel */
#define SAA6588_CMD_OPEN	_IOW('R', 1, int)
#define SAA6588_CMD_CLOSE	_IOW('R', 2, int)
#define SAA6588_CMD_READ	_IOR('R', 3, int)
#define SAA6588_CMD_POLL	_IOR('R', 4, int)

#endif
