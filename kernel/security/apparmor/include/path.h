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
#ifndef __AA_PATH_H
#define __AA_PATH_H


enum path_flags {
	PATH_IS_DIR = 0x1,		/* path is a directory */
	PATH_CONNECT_PATH = 0x4,	/* connect disconnected paths to / */
	PATH_CHROOT_REL = 0x8,		/* do path lookup relative to chroot */
	PATH_CHROOT_NSCONNECT = 0x10,	/* connect paths that are at ns root */

	PATH_DELEGATE_DELETED = 0x08000, /* delegate deleted files */
	PATH_MEDIATE_DELETED = 0x10000,	/* mediate deleted paths */
};

int aa_path_name(struct path *path, int flags, char **buffer,
		 const char **name, const char **info);

#endif /* __AA_PATH_H */
