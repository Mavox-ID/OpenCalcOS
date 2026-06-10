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
#ifndef __RTL8712_MACSETTING_BITDEF_H__
#define __RTL8712_MACSETTING_BITDEF_H__


/*MACID*/
/*BSSID*/

/*HWVID*/
#define	_HWVID_MSK				0x0F

/*MAR*/
/*MBIDCANCONTENT*/

/*MBIDCANCFG*/
#define	_POOLING				BIT(31)
#define	_WRITE_EN				BIT(16)
#define	_CAM_ADDR_MSK			0x001F
#define	_CAM_ADDR_SHT			0

/*BUILDTIME*/
#define _BUILDTIME_MSK			0x3FFFFFFF

/*BUILDUSER*/



#endif /* __RTL8712_MACSETTING_BITDEF_H__*/

