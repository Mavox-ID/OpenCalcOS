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
#ifdef __ASSEMBLY__
#define __val(x)	x
#else
#define __val(x)	(x)
#endif

#define DECOMPRESS_OFFSET_BASE	__val(0x00900000)
#define BOOT_RELOC_SIZE		__val(0x00001000)

#define KERNEL_EXEC_ADDR	__val(CONFIG_MEMORY_START)
#define KERNEL_DECOMPRESS_ADDR	__val(CONFIG_MEMORY_START + \
				      DECOMPRESS_OFFSET_BASE + BOOT_RELOC_SIZE)
#define KERNEL_ENTRY		__val(CONFIG_MEMORY_START + 0x1000)

#define BOOT_EXEC_ADDR		__val(CONFIG_MEMORY_START)
#define BOOT_RELOC_ADDR		__val(CONFIG_MEMORY_START + DECOMPRESS_OFFSET_BASE)
