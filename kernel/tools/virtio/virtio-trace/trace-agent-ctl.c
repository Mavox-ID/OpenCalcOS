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
#define _GNU_SOURCE
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "trace-agent.h"

#define HOST_MSG_SIZE		256
#define EVENT_WAIT_MSEC		100

static volatile sig_atomic_t global_signal_val;
bool global_sig_receive;	/* default false */
bool global_run_operation;	/* default false*/

/* Handle SIGTERM/SIGINT/SIGQUIT to exit */
static void signal_handler(int sig)
{
	global_signal_val = sig;
}

int rw_ctl_init(const char *ctl_path)
{
	int ctl_fd;

	ctl_fd = open(ctl_path, O_RDONLY);
	if (ctl_fd == -1) {
		pr_err("Cannot open ctl_fd\n");
		goto error;
	}

	return ctl_fd;

error:
	exit(EXIT_FAILURE);
}

static int wait_order(int ctl_fd)
{
	struct pollfd poll_fd;
	int ret = 0;

	while (!global_sig_receive) {
		poll_fd.fd = ctl_fd;
		poll_fd.events = POLLIN;

		ret = poll(&poll_fd, 1, EVENT_WAIT_MSEC);

		if (global_signal_val) {
			global_sig_receive = true;
			pr_info("Receive interrupt %d\n", global_signal_val);

			/* Wakes rw-threads when they are sleeping */
			if (!global_run_operation)
				pthread_cond_broadcast(&cond_wakeup);

			ret = -1;
			break;
		}

		if (ret < 0) {
			pr_err("Polling error\n");
			goto error;
		}

		if (ret)
			break;
	};

	return ret;

error:
	exit(EXIT_FAILURE);
}

/*
 * contol read/write threads by handling global_run_operation
 */
void *rw_ctl_loop(int ctl_fd)
{
	ssize_t rlen;
	char buf[HOST_MSG_SIZE];
	int ret;

	/* Setup signal handlers */
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);

	while (!global_sig_receive) {

		ret = wait_order(ctl_fd);
		if (ret < 0)
			break;

		rlen = read(ctl_fd, buf, sizeof(buf));
		if (rlen < 0) {
			pr_err("read data error in ctl thread\n");
			goto error;
		}

		if (rlen == 2 && buf[0] == '1') {
			/*
			 * If host writes '1' to a control path,
			 * this controller wakes all read/write threads.
			 */
			global_run_operation = true;
			pthread_cond_broadcast(&cond_wakeup);
			pr_debug("Wake up all read/write threads\n");
		} else if (rlen == 2 && buf[0] == '0') {
			/*
			 * If host writes '0' to a control path, read/write
			 * threads will wait for notification from Host.
			 */
			global_run_operation = false;
			pr_debug("Stop all read/write threads\n");
		} else
			pr_info("Invalid host notification: %s\n", buf);
	}

	return NULL;

error:
	exit(EXIT_FAILURE);
}
