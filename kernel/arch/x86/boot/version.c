/* -*- beep-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *
 *   This file is part of the Beep kernel, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

/*
 * Kernel version string
 */

#include "boot.h"
#include <generated/utsrelease.h>
#include <generated/compile.h>

const char kernel_version[] =
	UTS_RELEASE " (" BEEP_COMPILE_BY "@" BEEP_COMPILE_HOST ") "
	UTS_VERSION;
