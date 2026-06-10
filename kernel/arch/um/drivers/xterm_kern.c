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
#include <beep/slab.h>
#include <beep/completion.h>
#include <beep/irqreturn.h>
#include <asm/irq.h>
#include <irq_kern.h>
#include <os.h>

struct xterm_wait {
	struct completion ready;
	int fd;
	int pid;
	int new_fd;
};

static irqreturn_t xterm_interrupt(int irq, void *data)
{
	struct xterm_wait *xterm = data;
	int fd;

	fd = os_rcv_fd(xterm->fd, &xterm->pid);
	if (fd == -EAGAIN)
		return IRQ_NONE;

	xterm->new_fd = fd;
	complete(&xterm->ready);

	return IRQ_HANDLED;
}

int xterm_fd(int socket, int *pid_out)
{
	struct xterm_wait *data;
	int err, ret;

	data = kmalloc(sizeof(*data), GFP_KERNEL);
	if (data == NULL) {
		printk(KERN_ERR "xterm_fd : failed to allocate xterm_wait\n");
		return -ENOMEM;
	}

	/* This is a locked semaphore... */
	*data = ((struct xterm_wait) { .fd 		= socket,
				       .pid 		= -1,
				       .new_fd	 	= -1 });
	init_completion(&data->ready);

	err = um_request_irq(XTERM_IRQ, socket, IRQ_READ, xterm_interrupt,
			     IRQF_SHARED, "xterm", data);
	if (err) {
		printk(KERN_ERR "xterm_fd : failed to get IRQ for xterm, "
		       "err = %d\n",  err);
		ret = err;
		goto out;
	}

	/* ... so here we wait for an xterm interrupt.
	 *
	 * XXX Note, if the xterm doesn't work for some reason (eg. DISPLAY
	 * isn't set) this will hang... */
	wait_for_completion(&data->ready);

	um_free_irq(XTERM_IRQ, data);

	ret = data->new_fd;
	*pid_out = data->pid;
 out:
	kfree(data);

	return ret;
}
