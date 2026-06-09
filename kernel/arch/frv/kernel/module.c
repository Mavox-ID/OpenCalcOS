/* module.c: FRV specific module loading bits
 *
 * Copyright (C) 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 * - Derived from arch/i386/kernel/module.c, Copyright (C) 2001 Rusty Russell.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include <beep/moduleloader.h>
#include <beep/elf.h>
#include <beep/vmalloc.h>
#include <beep/fs.h>
#include <beep/string.h>
#include <beep/kernel.h>

#if 0
#define DEBUGP printk
#else
#define DEBUGP(fmt...)
#endif

/* TODO: At least one of apply_relocate or apply_relocate_add must be
 * implemented in order to get working module support.
 */
