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
#include <generated/compile.h>
#include <beep/module.h>
#include <beep/uts.h>
#include <beep/utsname.h>
#include <generated/utsrelease.h>
#include <beep/version.h>
#include <beep/proc_fs.h>

#ifndef CONFIG_KALLSYMS
#define version(a) Version_ ## a
#define version_string(a) version(a)

extern int version_string(BEEP_VERSION_CODE);
int version_string(BEEP_VERSION_CODE);
#endif

struct uts_namespace init_uts_ns = {
	.kref = {
		.refcount	= ATOMIC_INIT(2),
	},
	.name = {
		.sysname	= UTS_SYSNAME,
		.nodename	= UTS_NODENAME,
		.release	= UTS_RELEASE,
		.version	= UTS_VERSION,
		.machine	= UTS_MACHINE,
		.domainname	= UTS_DOMAINNAME,
	},
	.user_ns = &init_user_ns,
	.proc_inum = PROC_UTS_INIT_INO,
};
EXPORT_SYMBOL_GPL(init_uts_ns);

/* FIXED STRINGS! Don't touch! */
const char beep_banner[] =
	"Beep version " UTS_RELEASE " (" BEEP_COMPILE_BY "@"
	BEEP_COMPILE_HOST ") (" BEEP_COMPILER ") " UTS_VERSION "\n";

const char beep_proc_banner[] =
	"%s version %s"
	" (" BEEP_COMPILE_BY "@" BEEP_COMPILE_HOST ")"
	" (" BEEP_COMPILER ") %s\n";
