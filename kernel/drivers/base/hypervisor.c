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
#include <beep/kobject.h>
#include <beep/device.h>
#include <beep/export.h>
#include "base.h"

struct kobject *hypervisor_kobj;
EXPORT_SYMBOL_GPL(hypervisor_kobj);

int __init hypervisor_init(void)
{
	hypervisor_kobj = kobject_create_and_add("hypervisor", NULL);
	if (!hypervisor_kobj)
		return -ENOMEM;
	return 0;
}
