/* Null profiling driver
 *
 * Copyright (C) 2003  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * Licence.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */
#include <beep/kernel.h>
#include <beep/oprofile.h>
#include <beep/init.h>
#include <beep/errno.h>

int __init oprofile_arch_init(struct oprofile_operations *ops)
{
	return -ENODEV;
}

void oprofile_arch_exit(void)
{
}

