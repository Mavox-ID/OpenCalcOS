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
#include "qnx6.h"

struct dentry *qnx6_lookup(struct inode *dir, struct dentry *dentry,
				unsigned int flags)
{
	unsigned ino;
	struct page *page;
	struct inode *foundinode = NULL;
	const char *name = dentry->d_name.name;
	int len = dentry->d_name.len;

	if (len > QNX6_LONG_NAME_MAX)
		return ERR_PTR(-ENAMETOOLONG);

	ino = qnx6_find_entry(len, dir, name, &page);
	if (ino) {
		foundinode = qnx6_iget(dir->i_sb, ino);
		qnx6_put_page(page);
		if (IS_ERR(foundinode)) {
			QNX6DEBUG((KERN_ERR "qnx6: lookup->iget -> "
				" error %ld\n", PTR_ERR(foundinode)));
			return ERR_CAST(foundinode);
		}
	} else {
		QNX6DEBUG((KERN_INFO "qnx6_lookup: not found %s\n", name));
		return NULL;
	}
	d_add(dentry, foundinode);
	return NULL;
}
