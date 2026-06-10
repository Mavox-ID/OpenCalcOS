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
#include <stddef.h>
#include "types.h"
#include "elf.h"
#include "string.h"
#include "stdio.h"
#include "page.h"
#include "ops.h"

#include "of.h"

static void *of_stdout_handle;

static int of_console_open(void)
{
	void *devp;

	if (((devp = of_finddevice("/chosen")) != NULL)
	    && (of_getprop(devp, "stdout", &of_stdout_handle,
			   sizeof(of_stdout_handle))
		== sizeof(of_stdout_handle)))
		return 0;

	return -1;
}

static void of_console_write(const char *buf, int len)
{
	of_call_prom("write", 3, 1, of_stdout_handle, buf, len);
}

void of_console_init(void)
{
	console_ops.open = of_console_open;
	console_ops.write = of_console_write;
}
