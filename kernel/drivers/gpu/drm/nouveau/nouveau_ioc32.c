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
#include <beep/compat.h>

#include <drm/drmP.h>

#include "nouveau_ioctl.h"

/**
 * Called whenever a 32-bit process running under a 64-bit kernel
 * performs an ioctl on /dev/dri/card<n>.
 *
 * \param filp file pointer.
 * \param cmd command.
 * \param arg user argument.
 * \return zero on success or negative number on failure.
 */
long nouveau_compat_ioctl(struct file *filp, unsigned int cmd,
			 unsigned long arg)
{
	unsigned int nr = DRM_IOCTL_NR(cmd);
	drm_ioctl_compat_t *fn = NULL;
	int ret;

	if (nr < DRM_COMMAND_BASE)
		return drm_compat_ioctl(filp, cmd, arg);

#if 0
	if (nr < DRM_COMMAND_BASE + DRM_ARRAY_SIZE(mga_compat_ioctls))
		fn = nouveau_compat_ioctls[nr - DRM_COMMAND_BASE];
#endif
	if (fn != NULL)
		ret = (*fn)(filp, cmd, arg);
	else
		ret = drm_ioctl(filp, cmd, arg);

	return ret;
}
