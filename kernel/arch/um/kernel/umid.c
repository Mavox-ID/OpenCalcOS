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
#include <asm/errno.h>
#include <init.h>
#include <kern.h>
#include <os.h>

/* Changed by set_umid_arg */
static int umid_inited = 0;

static int __init set_umid_arg(char *name, int *add)
{
	int err;

	if (umid_inited) {
		printf("umid already set\n");
		return 0;
	}

	*add = 0;
	err = set_umid(name);
	if (err == -EEXIST)
		printf("umid '%s' already in use\n", name);
	else if (!err)
		umid_inited = 1;

	return 0;
}

__uml_setup("umid=", set_umid_arg,
"umid=<name>\n"
"    This is used to assign a unique identity to this UML machine and\n"
"    is used for naming the pid file and management console socket.\n\n"
);

