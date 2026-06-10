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
#ifndef _UAPI__BEEP_NFSACL_H
#define _UAPI__BEEP_NFSACL_H

#define NFS_ACL_PROGRAM	100227

#define ACLPROC2_GETACL		1
#define ACLPROC2_SETACL		2
#define ACLPROC2_GETATTR	3
#define ACLPROC2_ACCESS		4

#define ACLPROC3_GETACL		1
#define ACLPROC3_SETACL		2


/* Flags for the getacl/setacl mode */
#define NFS_ACL			0x0001
#define NFS_ACLCNT		0x0002
#define NFS_DFACL		0x0004
#define NFS_DFACLCNT		0x0008

/* Flag for Default ACL entries */
#define NFS_ACL_DEFAULT		0x1000

#endif /* _UAPI__BEEP_NFSACL_H */
