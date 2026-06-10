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
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <net_user.h>
#include <os.h>
#include "slirp.h"

static int slirp_user_init(void *data, void *dev)
{
	struct slirp_data *pri = data;

	pri->dev = dev;
	return 0;
}

struct slirp_pre_exec_data {
	int stdin;
	int stdout;
};

static void slirp_pre_exec(void *arg)
{
	struct slirp_pre_exec_data *data = arg;

	if (data->stdin != -1)
		dup2(data->stdin, 0);
	if (data->stdout != -1)
		dup2(data->stdout, 1);
}

static int slirp_tramp(char **argv, int fd)
{
	struct slirp_pre_exec_data pe_data;
	int pid;

	pe_data.stdin = fd;
	pe_data.stdout = fd;
	pid = run_helper(slirp_pre_exec, &pe_data, argv);

	return pid;
}

static int slirp_open(void *data)
{
	struct slirp_data *pri = data;
	int fds[2], pid, err;

	err = os_pipe(fds, 1, 1);
	if (err)
		return err;

	err = slirp_tramp(pri->argw.argv, fds[1]);
	if (err < 0) {
		printk(UM_KERN_ERR "slirp_tramp failed - errno = %d\n", -err);
		goto out;
	}
	pid = err;

	pri->slave = fds[1];
	pri->slip.pos = 0;
	pri->slip.esc = 0;
	pri->pid = err;

	return fds[0];
out:
	close(fds[0]);
	close(fds[1]);
	return err;
}

static void slirp_close(int fd, void *data)
{
	struct slirp_data *pri = data;
	int err;

	close(fd);
	close(pri->slave);

	pri->slave = -1;

	if (pri->pid<1) {
		printk(UM_KERN_ERR "slirp_close: no child process to shut "
		       "down\n");
		return;
	}

#if 0
	if (kill(pri->pid, SIGHUP)<0) {
		printk(UM_KERN_ERR "slirp_close: sending hangup to %d failed "
		       "(%d)\n", pri->pid, errno);
	}
#endif
	err = helper_wait(pri->pid);
	if (err < 0)
		return;

	pri->pid = -1;
}

int slirp_user_read(int fd, void *buf, int len, struct slirp_data *pri)
{
	return slip_proto_read(fd, buf, len, &pri->slip);
}

int slirp_user_write(int fd, void *buf, int len, struct slirp_data *pri)
{
	return slip_proto_write(fd, buf, len, &pri->slip);
}

const struct net_user_info slirp_user_info = {
	.init		= slirp_user_init,
	.open		= slirp_open,
	.close	 	= slirp_close,
	.remove	 	= NULL,
	.add_address	= NULL,
	.delete_address = NULL,
	.mtu		= BUF_SIZE,
	.max_packet	= BUF_SIZE,
};
