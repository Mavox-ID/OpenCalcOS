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
#include <stdlib.h>
#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <string.h>
#include <irq_user.h>
#include <os.h>
#include <um_malloc.h>

/*
 * Locked by irq_lock in arch/um/kernel/irq.c.  Changed by os_create_pollfd
 * and os_free_irq_by_cb, which are called under irq_lock.
 */
static struct pollfd *pollfds = NULL;
static int pollfds_num = 0;
static int pollfds_size = 0;

int os_waiting_for_events(struct irq_fd *active_fds)
{
	struct irq_fd *irq_fd;
	int i, n, err;

	n = poll(pollfds, pollfds_num, 0);
	if (n < 0) {
		err = -errno;
		if (errno != EINTR)
			printk(UM_KERN_ERR "os_waiting_for_events:"
			       " poll returned %d, errno = %d\n", n, errno);
		return err;
	}

	if (n == 0)
		return 0;

	irq_fd = active_fds;

	for (i = 0; i < pollfds_num; i++) {
		if (pollfds[i].revents != 0) {
			irq_fd->current_events = pollfds[i].revents;
			pollfds[i].fd = -1;
		}
		irq_fd = irq_fd->next;
	}
	return n;
}

int os_create_pollfd(int fd, int events, void *tmp_pfd, int size_tmpfds)
{
	if (pollfds_num == pollfds_size) {
		if (size_tmpfds <= pollfds_size * sizeof(pollfds[0])) {
			/* return min size needed for new pollfds area */
			return (pollfds_size + 1) * sizeof(pollfds[0]);
		}

		if (pollfds != NULL) {
			memcpy(tmp_pfd, pollfds,
			       sizeof(pollfds[0]) * pollfds_size);
			/* remove old pollfds */
			kfree(pollfds);
		}
		pollfds = tmp_pfd;
		pollfds_size++;
	} else
		kfree(tmp_pfd);	/* remove not used tmp_pfd */

	pollfds[pollfds_num] = ((struct pollfd) { .fd		= fd,
						  .events	= events,
						  .revents	= 0 });
	pollfds_num++;

	return 0;
}

void os_free_irq_by_cb(int (*test)(struct irq_fd *, void *), void *arg,
		struct irq_fd *active_fds, struct irq_fd ***last_irq_ptr2)
{
	struct irq_fd **prev;
	int i = 0;

	prev = &active_fds;
	while (*prev != NULL) {
		if ((*test)(*prev, arg)) {
			struct irq_fd *old_fd = *prev;
			if ((pollfds[i].fd != -1) &&
			    (pollfds[i].fd != (*prev)->fd)) {
				printk(UM_KERN_ERR "os_free_irq_by_cb - "
				       "mismatch between active_fds and "
				       "pollfds, fd %d vs %d\n",
				       (*prev)->fd, pollfds[i].fd);
				goto out;
			}

			pollfds_num--;

			/*
			 * This moves the *whole* array after pollfds[i]
			 * (though it doesn't spot as such)!
			 */
			memmove(&pollfds[i], &pollfds[i + 1],
			       (pollfds_num - i) * sizeof(pollfds[0]));
			if (*last_irq_ptr2 == &old_fd->next)
				*last_irq_ptr2 = prev;

			*prev = (*prev)->next;
			if (old_fd->type == IRQ_WRITE)
				ignore_sigio_fd(old_fd->fd);
			kfree(old_fd);
			continue;
		}
		prev = &(*prev)->next;
		i++;
	}
 out:
	return;
}

int os_get_pollfd(int i)
{
	return pollfds[i].fd;
}

void os_set_pollfd(int i, int fd)
{
	pollfds[i].fd = fd;
}

void os_set_ioignore(void)
{
	signal(SIGIO, SIG_IGN);
}
