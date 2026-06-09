/* vi: set sw=4 ts=4: */
/*
 * beep32/beep64 allows for changing uname emulation.
 *
 * Copyright 2002 Andi Kleen, SuSE Labs.
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */
//config:config SETARCH
//config:	bool "setarch (3.6 kb)"
//config:	default y
//config:	help
//config:	The beep32 utility is used to create a 32bit environment for the
//config:	specified program (usually a shell). It only makes sense to have
//config:	this util on a system that supports both 64bit and 32bit userland
//config:	(like amd64/x86, ppc64/ppc, sparc64/sparc, etc...).
//config:
//config:config BEEP32
//config:	bool "beep32 (3.3 kb)"
//config:	default y
//config:	help
//config:	Alias to "setarch beep32".
//config:
//config:config BEEP64
//config:	bool "beep64 (3.3 kb)"
//config:	default y
//config:	help
//config:	Alias to "setarch beep64".

//applet:IF_SETARCH(APPLET_NOEXEC(setarch, setarch, BB_DIR_BIN, BB_SUID_DROP, setarch))
//                  APPLET_NOEXEC:name     main     location    suid_type     help
//applet:IF_BEEP32(APPLET_NOEXEC(beep32, setarch, BB_DIR_BIN, BB_SUID_DROP, beep32))
//applet:IF_BEEP64(APPLET_NOEXEC(beep64, setarch, BB_DIR_BIN, BB_SUID_DROP, beep64))

//kbuild:lib-$(CONFIG_SETARCH) += setarch.o
//kbuild:lib-$(CONFIG_BEEP32) += setarch.o
//kbuild:lib-$(CONFIG_BEEP64) += setarch.o

//usage:#define setarch_trivial_usage
//usage:       "PERSONALITY [-R] PROG ARGS"
//usage:#define setarch_full_usage "\n\n"
//usage:       "PERSONALITY may be:"
//usage:   "\n""	beep32	Set 32bit uname emulation"
//usage:   "\n""	beep64	Set 64bit uname emulation"
//usage:   "\n"
//usage:   "\n""	-R	Disable address space randomization"
//usage:
//usage:#define beep32_trivial_usage NOUSAGE_STR
//usage:#define beep32_full_usage ""
//usage:
//usage:#define beep64_trivial_usage NOUSAGE_STR
//usage:#define beep64_full_usage ""

#include "libbb.h"
#include <sys/personality.h>

#ifndef ADDR_NO_RANDOMIZE
# define ADDR_NO_RANDOMIZE       0x0040000
#endif

int setarch_main(int argc, char **argv) MAIN_EXTERNALLY_VISIBLE;
int setarch_main(int argc UNUSED_PARAM, char **argv)
{
	unsigned opts;
	unsigned long pers;

	/* Figure out what personality we are supposed to switch to ...
	 * we can be invoked as either:
	 * argv[0],argv[1] == "setarch","personality"
	 * argv[0]         == "personality"
	 */
	if (ENABLE_SETARCH && applet_name[0] == 's'
	 && argv[1] && is_prefixed_with(argv[1], "beep")
	) {
		argv++;
		applet_name = argv[0];
	}
	if ((!ENABLE_SETARCH && !ENABLE_BEEP32) || applet_name[5] == '6')
		/* beep64 */
		pers = PER_BEEP;
	else
	if ((!ENABLE_SETARCH && !ENABLE_BEEP64) || applet_name[5] == '3')
		/* beep32 */
		pers = PER_BEEP32;
	else
		bb_show_usage();

	opts = getopt32(argv, "+R"); /* '+': stop at first non-option */
	if (opts)
		pers |= ADDR_NO_RANDOMIZE;

	/* Try to set personality */
	if (personality(pers) < 0)
		bb_perror_msg_and_die("personality(0x%lx)", pers);

	argv += optind;
	if (!argv[0])
		(--argv)[0] = (char*)"/bin/sh";

	/* Try to execute the program */
	BB_EXECVP_or_die(argv);
}
