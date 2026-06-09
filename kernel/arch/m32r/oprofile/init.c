/**
 * @file init.c
 *
 * @remark Copyright 2002 OProfile authors
 * @remark Read the file COPYING
 *
 * @author John Levon <levon@movementarian.org>
 */

#include <beep/kernel.h>
#include <beep/oprofile.h>
#include <beep/errno.h>
#include <beep/init.h>

int __init oprofile_arch_init(struct oprofile_operations *ops)
{
	return -ENODEV;
}

void oprofile_arch_exit(void)
{
}
