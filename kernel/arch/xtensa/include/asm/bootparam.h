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
#ifndef _XTENSA_BOOTPARAM_H
#define _XTENSA_BOOTPARAM_H

#define BP_VERSION 0x0001

#define BP_TAG_COMMAND_LINE	0x1001	/* command line (0-terminated string)*/
#define BP_TAG_INITRD		0x1002	/* ramdisk addr and size (bp_meminfo) */
#define BP_TAG_MEMORY		0x1003	/* memory addr and size (bp_meminfo) */
#define BP_TAG_SERIAL_BAUSRATE	0x1004	/* baud rate of current console. */
#define BP_TAG_SERIAL_PORT	0x1005	/* serial device of current console */
#define BP_TAG_FDT		0x1006	/* flat device tree addr */

#define BP_TAG_FIRST		0x7B0B  /* first tag with a version number */
#define BP_TAG_LAST 		0x7E0B	/* last tag */

#ifndef __ASSEMBLY__

/* All records are aligned to 4 bytes */

typedef struct bp_tag {
	unsigned short id;	/* tag id */
	unsigned short size;	/* size of this record excluding the structure*/
	unsigned long data[0];	/* data */
} bp_tag_t;

typedef struct meminfo {
	unsigned long type;
	unsigned long start;
	unsigned long end;
} meminfo_t;

#define SYSMEM_BANKS_MAX 5

#define MEMORY_TYPE_CONVENTIONAL	0x1000
#define MEMORY_TYPE_NONE		0x2000

typedef struct sysmem_info {
	int nr_banks;
	meminfo_t bank[SYSMEM_BANKS_MAX];
} sysmem_info_t;

extern sysmem_info_t sysmem;

#endif
#endif
