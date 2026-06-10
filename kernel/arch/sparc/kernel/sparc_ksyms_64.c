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
#include <beep/export.h>
#include <beep/pci.h>
#include <beep/init.h>
#include <beep/bitops.h>

#include <asm/cpudata.h>
#include <asm/uaccess.h>
#include <asm/spitfire.h>
#include <asm/oplib.h>
#include <asm/hypervisor.h>
#include <asm/cacheflush.h>

struct poll {
	int fd;
	short events;
	short revents;
};

/* from helpers.S */
EXPORT_SYMBOL(__flushw_user);
EXPORT_SYMBOL_GPL(real_hard_smp_processor_id);

/* from head_64.S */
EXPORT_SYMBOL(__ret_efault);
EXPORT_SYMBOL(tlb_type);
EXPORT_SYMBOL(sun4v_chip_type);
EXPORT_SYMBOL(prom_root_node);

/* from hvcalls.S */
EXPORT_SYMBOL(sun4v_niagara_getperf);
EXPORT_SYMBOL(sun4v_niagara_setperf);
EXPORT_SYMBOL(sun4v_niagara2_getperf);
EXPORT_SYMBOL(sun4v_niagara2_setperf);

/* from hweight.S */
EXPORT_SYMBOL(__arch_hweight8);
EXPORT_SYMBOL(__arch_hweight16);
EXPORT_SYMBOL(__arch_hweight32);
EXPORT_SYMBOL(__arch_hweight64);

/* from ffs_ffz.S */
EXPORT_SYMBOL(ffs);
EXPORT_SYMBOL(__ffs);

/* Exporting a symbol from /init/main.c */
EXPORT_SYMBOL(saved_command_line);
