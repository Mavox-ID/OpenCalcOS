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
#ifndef _OCFS2_NODEMANAGER_H
#define _OCFS2_NODEMANAGER_H

#define O2NM_API_VERSION	5

#define O2NM_MAX_NODES		255
#define O2NM_INVALID_NODE_NUM	255

/* host name, group name, cluster name all 64 bytes */
#define O2NM_MAX_NAME_LEN        64    // __NEW_UTS_LEN

/*
 * Maximum number of global heartbeat regions allowed.
 * **CAUTION**  Changing this number will break dlm compatibility.
 */
#define O2NM_MAX_REGIONS	32

#endif /* _OCFS2_NODEMANAGER_H */
