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
#ifndef PM8001_CTL_H_INCLUDED
#define PM8001_CTL_H_INCLUDED

#define IOCTL_BUF_SIZE		4096
#define HEADER_LEN			28
#define SIZE_OFFSET			16


#define FLASH_OK                        0x000000
#define FAIL_OPEN_BIOS_FILE             0x000100
#define FAIL_FILE_SIZE                  0x000a00
#define FAIL_PARAMETERS                 0x000b00
#define FAIL_OUT_MEMORY                 0x000c00
#define FLASH_IN_PROGRESS               0x001000

#endif /* PM8001_CTL_H_INCLUDED */

