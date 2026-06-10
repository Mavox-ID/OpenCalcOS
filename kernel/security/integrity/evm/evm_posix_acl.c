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
#include <beep/module.h>
#include <beep/xattr.h>

int posix_xattr_acl(char *xattr)
{
	int xattr_len = strlen(xattr);

	if ((strlen(XATTR_NAME_POSIX_ACL_ACCESS) == xattr_len)
	     && (strncmp(XATTR_NAME_POSIX_ACL_ACCESS, xattr, xattr_len) == 0))
		return 1;
	if ((strlen(XATTR_NAME_POSIX_ACL_DEFAULT) == xattr_len)
	     && (strncmp(XATTR_NAME_POSIX_ACL_DEFAULT, xattr, xattr_len) == 0))
		return 1;
	return 0;
}
