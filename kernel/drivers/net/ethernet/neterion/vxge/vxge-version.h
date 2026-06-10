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
#ifndef VXGE_VERSION_H
#define VXGE_VERSION_H

#define VXGE_VERSION_MAJOR	"2"
#define VXGE_VERSION_MINOR	"5"
#define VXGE_VERSION_FIX	"3"
#define VXGE_VERSION_BUILD	"22640"
#define VXGE_VERSION_FOR	"k"

#define VXGE_FW_VER(maj, min, bld) (((maj) << 16) + ((min) << 8) + (bld))

#define VXGE_DEAD_FW_VER_MAJOR	1
#define VXGE_DEAD_FW_VER_MINOR	4
#define VXGE_DEAD_FW_VER_BUILD	4

#define VXGE_FW_DEAD_VER VXGE_FW_VER(VXGE_DEAD_FW_VER_MAJOR, \
				     VXGE_DEAD_FW_VER_MINOR, \
				     VXGE_DEAD_FW_VER_BUILD)

#define VXGE_EPROM_FW_VER_MAJOR	1
#define VXGE_EPROM_FW_VER_MINOR	6
#define VXGE_EPROM_FW_VER_BUILD	1

#define VXGE_EPROM_FW_VER VXGE_FW_VER(VXGE_EPROM_FW_VER_MAJOR, \
				      VXGE_EPROM_FW_VER_MINOR, \
				      VXGE_EPROM_FW_VER_BUILD)

#define VXGE_CERT_FW_VER_MAJOR	1
#define VXGE_CERT_FW_VER_MINOR	8
#define VXGE_CERT_FW_VER_BUILD	1

#define VXGE_CERT_FW_VER VXGE_FW_VER(VXGE_CERT_FW_VER_MAJOR, \
				     VXGE_CERT_FW_VER_MINOR, \
				     VXGE_CERT_FW_VER_BUILD)

#endif
