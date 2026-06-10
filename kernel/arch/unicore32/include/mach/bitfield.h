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
#ifndef __MACH_PUV3_BITFIELD_H__
#define __MACH_PUV3_BITFIELD_H__

#ifndef __ASSEMBLY__
#define UData(Data)	((unsigned long) (Data))
#else
#define UData(Data)	(Data)
#endif

#define FIELD(val, vmask, vshift)	(((val) & ((UData(1) << (vmask)) - 1)) << (vshift))
#define FMASK(vmask, vshift)		(((UData(1) << (vmask)) - 1) << (vshift))

#endif /* __MACH_PUV3_BITFIELD_H__ */
