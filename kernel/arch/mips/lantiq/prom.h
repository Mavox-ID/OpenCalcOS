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
#ifndef _LTQ_PROM_H__
#define _LTQ_PROM_H__

#define LTQ_SYS_TYPE_LEN	0x100
#define LTQ_SYS_REV_LEN         0x10

struct ltq_soc_info {
	unsigned char *name;
	unsigned int rev;
	unsigned char rev_type[LTQ_SYS_REV_LEN];
	unsigned int srev;
	unsigned int partnum;
	unsigned int type;
	unsigned char sys_type[LTQ_SYS_TYPE_LEN];
	unsigned char *compatible;
};

extern void ltq_soc_detect(struct ltq_soc_info *i);
extern void ltq_soc_init(void);

extern struct boot_param_header __dtb_start;

#endif
