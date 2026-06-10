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
#include <core/object.h>
#include <core/client.h>
#include <core/subdev.h>
#include <core/printk.h>

void
nv_printk_(struct nouveau_object *object, const char *pfx, int level,
	   const char *fmt, ...)
{
	static const char name[] = { '!', 'E', 'W', ' ', 'D', 'T', 'P', 'S' };
	char mfmt[256];
	va_list args;

	if (object && !nv_iclass(object, NV_CLIENT_CLASS)) {
		struct nouveau_object *device = object;
		struct nouveau_object *subdev = object;
		char obuf[64], *ofmt = "";

		if (object->engine) {
			snprintf(obuf, sizeof(obuf), "[0x%08x][%p]",
				 nv_hclass(object), object);
			ofmt = obuf;
			subdev = object->engine;
			device = object->engine;
		}

		if (subdev->parent)
			device = subdev->parent;

		if (level > nv_subdev(subdev)->debug)
			return;

		snprintf(mfmt, sizeof(mfmt), "%snouveau %c[%8s][%s]%s %s", pfx,
			 name[level], nv_subdev(subdev)->name,
			 nv_device(device)->name, ofmt, fmt);
	} else
	if (object && nv_iclass(object, NV_CLIENT_CLASS)) {
		if (level > nv_client(object)->debug)
			return;

		snprintf(mfmt, sizeof(mfmt), "%snouveau %c[%8s] %s", pfx,
			 name[level], nv_client(object)->name, fmt);
	} else {
		snprintf(mfmt, sizeof(mfmt), "%snouveau: %s", pfx, fmt);
	}

	va_start(args, fmt);
	vprintk(mfmt, args);
	va_end(args);
}
