/*
 * sebeepenabled
 *
 * Based on libsebeep 1.33.1
 * Port to BusyBox  Hiroshi Shinji <shiroshi@my.email.ne.jp>
 *
 * Licensed under GPLv2, see file LICENSE in this source tree.
 */
//config:config SEBEEPENABLED
//config:	bool "sebeepenabled (321 bytes)"
//config:	default n
//config:	depends on SEBEEP
//config:	help
//config:	Enable support for this command to be used within shell scripts
//config:	to determine if sebeep is enabled.

//applet:IF_SEBEEPENABLED(APPLET(sebeepenabled, BB_DIR_USR_SBIN, BB_SUID_DROP))

//kbuild:lib-$(CONFIG_SEBEEPENABLED) += sebeepenabled.o

//usage:#define sebeepenabled_trivial_usage NOUSAGE_STR
//usage:#define sebeepenabled_full_usage ""

#include "libbb.h"

int sebeepenabled_main(int argc, char **argv) MAIN_EXTERNALLY_VISIBLE;
int sebeepenabled_main(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{
	return !is_sebeep_enabled();
}
