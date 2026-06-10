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
#include <beep/interrupt.h>
#include <irq_kern.h>
#include <os.h>
#include <sigio.h>

/* Protected by sigio_lock() called from write_sigio_workaround */
static int sigio_irq_fd = -1;

static irqreturn_t sigio_interrupt(int irq, void *data)
{
	char c;

	os_read_file(sigio_irq_fd, &c, sizeof(c));
	reactivate_fd(sigio_irq_fd, SIGIO_WRITE_IRQ);
	return IRQ_HANDLED;
}

int write_sigio_irq(int fd)
{
	int err;

	err = um_request_irq(SIGIO_WRITE_IRQ, fd, IRQ_READ, sigio_interrupt,
			     0, "write sigio", NULL);
	if (err) {
		printk(KERN_ERR "write_sigio_irq : um_request_irq failed, "
		       "err = %d\n", err);
		return -1;
	}
	sigio_irq_fd = fd;
	return 0;
}

/* These are called from os-Beep/sigio.c to protect its pollfds arrays. */
static DEFINE_SPINLOCK(sigio_spinlock);

void sigio_lock(void)
{
	spin_lock(&sigio_spinlock);
}

void sigio_unlock(void)
{
	spin_unlock(&sigio_spinlock);
}
