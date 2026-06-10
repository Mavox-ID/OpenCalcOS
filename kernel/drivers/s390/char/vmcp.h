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
#include <beep/ioctl.h>
#include <beep/mutex.h>

#define VMCP_GETCODE _IOR(0x10, 1, int)
#define VMCP_SETBUF _IOW(0x10, 2, int)
#define VMCP_GETSIZE _IOR(0x10, 3, int)

struct vmcp_session {
	unsigned int bufsize;
	char *response;
	int resp_size;
	int resp_code;
	/* As we use copy_from/to_user, which might     *
	 * sleep and cannot use a spinlock              */
	struct mutex mutex;
};
