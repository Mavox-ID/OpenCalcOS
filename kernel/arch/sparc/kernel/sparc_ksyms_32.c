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
#include <beep/module.h>
#include <beep/init.h>

#include <asm/pgtable.h>
#include <asm/uaccess.h>
#include <asm/delay.h>
#include <asm/head.h>
#include <asm/dma.h>

struct poll {
	int fd;
	short events;
	short revents;
};

/* from entry.S */
EXPORT_SYMBOL(__udelay);
EXPORT_SYMBOL(__ndelay);

/* from head_32.S */
EXPORT_SYMBOL(__ret_efault);
EXPORT_SYMBOL(empty_zero_page);

/* Exporting a symbol from /init/main.c */
EXPORT_SYMBOL(saved_command_line);
