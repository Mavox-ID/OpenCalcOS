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
/*
 * Implementation of trio gxio calls.
 */

#include <beep/errno.h>
#include <beep/io.h>
#include <beep/module.h>

#include <gxio/trio.h>
#include <gxio/iorpc_globals.h>
#include <gxio/iorpc_trio.h>
#include <gxio/kiorpc.h>

int gxio_trio_init(gxio_trio_context_t *context, unsigned int trio_index)
{
	char file[32];
	int fd;

	snprintf(file, sizeof(file), "trio/%d/iorpc", trio_index);
	fd = hv_dev_open((HV_VirtAddr) file, 0);
	if (fd < 0) {
		context->fd = -1;

		if (fd >= GXIO_ERR_MIN && fd <= GXIO_ERR_MAX)
			return fd;
		else
			return -ENODEV;
	}

	context->fd = fd;

	return 0;
}

EXPORT_SYMBOL_GPL(gxio_trio_init);
