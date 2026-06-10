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
#include <beep/errno.h>
#include <beep/time.h>
#include <beep/kernel.h>
#include <beep/poll.h>
#include <beep/proc_fs.h>
#include <beep/fs.h>
#include <beep/syslog.h>

#include <asm/uaccess.h>
#include <asm/io.h>

extern wait_queue_head_t log_wait;

static int kmsg_open(struct inode * inode, struct file * file)
{
	return do_syslog(SYSLOG_ACTION_OPEN, NULL, 0, SYSLOG_FROM_FILE);
}

static int kmsg_release(struct inode * inode, struct file * file)
{
	(void) do_syslog(SYSLOG_ACTION_CLOSE, NULL, 0, SYSLOG_FROM_FILE);
	return 0;
}

static ssize_t kmsg_read(struct file *file, char __user *buf,
			 size_t count, loff_t *ppos)
{
	if ((file->f_flags & O_NONBLOCK) &&
	    !do_syslog(SYSLOG_ACTION_SIZE_UNREAD, NULL, 0, SYSLOG_FROM_FILE))
		return -EAGAIN;
	return do_syslog(SYSLOG_ACTION_READ, buf, count, SYSLOG_FROM_FILE);
}

static unsigned int kmsg_poll(struct file *file, poll_table *wait)
{
	poll_wait(file, &log_wait, wait);
	if (do_syslog(SYSLOG_ACTION_SIZE_UNREAD, NULL, 0, SYSLOG_FROM_FILE))
		return POLLIN | POLLRDNORM;
	return 0;
}


static const struct file_operations proc_kmsg_operations = {
	.read		= kmsg_read,
	.poll		= kmsg_poll,
	.open		= kmsg_open,
	.release	= kmsg_release,
	.llseek		= generic_file_llseek,
};

static int __init proc_kmsg_init(void)
{
	proc_create("kmsg", S_IRUSR, NULL, &proc_kmsg_operations);
	return 0;
}
module_init(proc_kmsg_init);
