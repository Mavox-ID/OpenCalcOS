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
#ifndef BEEP_NBD_H
#define BEEP_NBD_H


#include <beep/wait.h>
#include <beep/mutex.h>
#include <uapi/beep/nbd.h>

struct request;

struct nbd_device {
	int flags;
	int harderror;		/* Code of hard error			*/
	struct socket * sock;
	struct file * file; 	/* If == NULL, device is not ready, yet	*/
	int magic;

	spinlock_t queue_lock;
	struct list_head queue_head;	/* Requests waiting result */
	struct request *active_req;
	wait_queue_head_t active_wq;
	struct list_head waiting_queue;	/* Requests to be sent */
	wait_queue_head_t waiting_wq;

	struct mutex tx_lock;
	struct gendisk *disk;
	int blksize;
	u64 bytesize;
	pid_t pid; /* pid of nbd-client, if attached */
	int xmit_timeout;
};

#endif
