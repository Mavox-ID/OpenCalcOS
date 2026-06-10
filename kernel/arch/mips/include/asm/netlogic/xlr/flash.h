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
#ifndef _ASM_NLM_FLASH_H_
#define _ASM_NLM_FLASH_H_

#define FLASH_CSBASE_ADDR(cs)		(cs)
#define FLASH_CSADDR_MASK(cs)		(0x10 + (cs))
#define FLASH_CSDEV_PARM(cs)		(0x20 + (cs))
#define FLASH_CSTIME_PARMA(cs)		(0x30 + (cs))
#define FLASH_CSTIME_PARMB(cs)		(0x40 + (cs))

#define FLASH_INT_MASK			0x50
#define FLASH_INT_STATUS		0x60
#define FLASH_ERROR_STATUS		0x70
#define FLASH_ERROR_ADDR		0x80

#define FLASH_NAND_CLE(cs)		(0x90 + (cs))
#define FLASH_NAND_ALE(cs)		(0xa0 + (cs))

#define FLASH_NAND_CSDEV_PARAM		0x000041e6
#define FLASH_NAND_CSTIME_PARAMA	0x4f400e22
#define FLASH_NAND_CSTIME_PARAMB	0x000083cf

#endif
