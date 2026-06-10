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
#ifndef __RTL8712_TIMECTRL_BITDEF_H__
#define __RTL8712_TIMECTRL_BITDEF_H__

/*TSFTR*/
/*SLOT*/
/*USTIME*/

/*TUBASE*/
#define	_TUBASE_MSK			0x07FF

/*SIFS_CCK*/
#define	_SIFS_CCK_TRX_MSK		0xFF00
#define	_SIFS_CCK_TRX_SHT		0x8
#define	_SIFS_CCK_CTX_MSK		0x00FF
#define	_SIFS_CCK_CTX_SHT		0

/*SIFS_OFDM*/
#define	_SIFS_OFDM_TRX_MSK		0xFF00
#define	_SIFS_OFDM_TRX_SHT		0x8
#define	_SIFS_OFDM_CTX_MSK		0x00FF
#define	_SIFS_OFDM_CTX_SHT		0

/*PIFS*/
/*ACKTO*/
/*EIFS*/
/*BCNITV*/
/*ATIMWND*/

/*DRVERLYINT*/
#define	_ENSWBCN				BIT(15)
#define	_DRVERLY_TU_MSK			0x0FF0
#define	_DRVERLY_TU_SHT			4
#define	_DRVERLY_US_MSK			0x000F
#define	_DRVERLY_US_SHT			0

/*BCNDMATIM*/
#define	_BCNDMATIM_MSK			0x03FF

/*BCNERRTH*/
/*MLT*/


#endif /* __RTL8712_TIMECTRL_BITDEF_H__*/

