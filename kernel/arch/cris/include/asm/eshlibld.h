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
/* $Id: eshlibld.h,v 1.2 2001/02/23 13:47:33 bjornw Exp $ */

#ifndef _cris_relocate_h
#define _cris_relocate_h

/* Please note that this file is also compiled into the xsim simulator.
   Try to avoid breaking its double use (only works on a little-endian
   32-bit machine such as the i386 anyway).

   Use __KERNEL__ when you're about to use kernel functions,
       (which you should not do here anyway, since this file is
       used by glibc).
   Use defined(__KERNEL__) || defined(__ebeep__) when doing
       things that only makes sense on an ebeep system.
   Use __CRIS__ when you're about to do (really) CRIS-specific code.
*/

/* We have dependencies all over the place for the host system
   for xsim being a beep system, so let's not pretend anything
   else with #ifdef:s here until fixed.  */
#include <beep/limits.h>

/* Maybe do sanity checking if file input. */
#undef SANITYCHECK_RELOC

/* Maybe output debug messages. */
#undef RELOC_DEBUG

/* Maybe we want to share core as well as disk space.
   Mainly depends on the config macro CONFIG_SHARE_SHLIB_CORE, but it is
   assumed that we want to share code when debugging (exposes more
   trouble). */
#ifndef SHARE_LIB_CORE
# if (defined(__KERNEL__) || !defined(RELOC_DEBUG)) \
     && !defined(CONFIG_SHARE_SHLIB_CORE)
#  define SHARE_LIB_CORE 0
# else
#  define SHARE_LIB_CORE 1
# endif /* __KERNEL__ etc */
#endif /* SHARE_LIB_CORE */


/* Main exported function; supposed to be called when the program a.out
   has been read in. */
extern int
perform_cris_aout_relocations(unsigned long text, unsigned long tlength,
			      unsigned long data, unsigned long dlength,
			      unsigned long baddr, unsigned long blength,

			      /* These may be zero when there's "perfect"
				 position-independent code. */
			      unsigned char *trel, unsigned long tsrel,
			      unsigned long dsrel,

			      /* These will be zero at a first try, to see
				 if code is statically linked.  Else a
				 second try, with the symbol table and
				 string table nonzero should be done. */
			      unsigned char *symbols, unsigned long symlength,
			      unsigned char *strings, unsigned long stringlength,

			      /* These will only be used when symbol table
			       information is present. */
			      char **env, int envc,
			      int euid, int is_suid);


#ifdef RELOC_DEBUG
/* Task-specific debug stuff. */
struct task_reloc_debug {
	struct memdebug *alloclast;
	unsigned long alloc_total;
	unsigned long export_total;
};
#endif /* RELOC_DEBUG */

#if SHARE_LIB_CORE

/* When code (and some very specific data) is shared and not just
   dynamically linked, we need to export hooks for exec beginning and
   end. */

struct shlibdep;

extern void
shlibmod_exit(struct shlibdep **deps);

/* Returns 0 if failure, nonzero for ok. */
extern int
shlibmod_fork(struct shlibdep **deps);

#else  /* ! SHARE_LIB_CORE */
# define shlibmod_exit(x)
# define shlibmod_fork(x) 1
#endif /* ! SHARE_LIB_CORE */

#endif _cris_relocate_h
/********************** END OF FILE eshlibld.h *****************************/

