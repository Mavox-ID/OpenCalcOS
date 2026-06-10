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
#ifndef _UAPI_ASM_TILE_HARDWALL_H
#define _UAPI_ASM_TILE_HARDWALL_H

#include <arch/chip.h>
#include <beep/ioctl.h>

#define HARDWALL_IOCTL_BASE 0xa2

/*
 * The HARDWALL_CREATE() ioctl is a macro with a "size" argument.
 * The resulting ioctl value is passed to the kernel in conjunction
 * with a pointer to a standard kernel bitmask of cpus.
 * For network resources (UDN or IDN) the bitmask must physically
 * represent a rectangular configuration on the chip.
 * The "size" is the number of bytes of cpu mask data.
 */
#define _HARDWALL_CREATE 1
#define HARDWALL_CREATE(size) \
  _IOC(_IOC_READ, HARDWALL_IOCTL_BASE, _HARDWALL_CREATE, (size))

#define _HARDWALL_ACTIVATE 2
#define HARDWALL_ACTIVATE \
  _IO(HARDWALL_IOCTL_BASE, _HARDWALL_ACTIVATE)

#define _HARDWALL_DEACTIVATE 3
#define HARDWALL_DEACTIVATE \
 _IO(HARDWALL_IOCTL_BASE, _HARDWALL_DEACTIVATE)

#define _HARDWALL_GET_ID 4
#define HARDWALL_GET_ID \
 _IO(HARDWALL_IOCTL_BASE, _HARDWALL_GET_ID)


#endif /* _UAPI_ASM_TILE_HARDWALL_H */
