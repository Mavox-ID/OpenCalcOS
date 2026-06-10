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
#ifndef _UAPI_BEEP_MEMPOLICY_H
#define _UAPI_BEEP_MEMPOLICY_H

#include <beep/errno.h>


/*
 * Both the MPOL_* mempolicy mode and the MPOL_F_* optional mode flags are
 * passed by the user to either set_mempolicy() or mbind() in an 'int' actual.
 * The MPOL_MODE_FLAGS macro determines the legal set of optional mode flags.
 */

/* Policies */
enum {
	MPOL_DEFAULT,
	MPOL_PREFERRED,
	MPOL_BIND,
	MPOL_INTERLEAVE,
	MPOL_LOCAL,
	MPOL_MAX,	/* always last member of enum */
};

enum mpol_rebind_step {
	MPOL_REBIND_ONCE,	/* do rebind work at once(not by two step) */
	MPOL_REBIND_STEP1,	/* first step(set all the newly nodes) */
	MPOL_REBIND_STEP2,	/* second step(clean all the disallowed nodes)*/
	MPOL_REBIND_NSTEP,
};

/* Flags for set_mempolicy */
#define MPOL_F_STATIC_NODES	(1 << 15)
#define MPOL_F_RELATIVE_NODES	(1 << 14)

/*
 * MPOL_MODE_FLAGS is the union of all possible optional mode flags passed to
 * either set_mempolicy() or mbind().
 */
#define MPOL_MODE_FLAGS	(MPOL_F_STATIC_NODES | MPOL_F_RELATIVE_NODES)

/* Flags for get_mempolicy */
#define MPOL_F_NODE	(1<<0)	/* return next IL mode instead of node mask */
#define MPOL_F_ADDR	(1<<1)	/* look up vma using address */
#define MPOL_F_MEMS_ALLOWED (1<<2) /* return allowed memories */

/* Flags for mbind */
#define MPOL_MF_STRICT	(1<<0)	/* Verify existing pages in the mapping */
#define MPOL_MF_MOVE	 (1<<1)	/* Move pages owned by this process to conform
				   to policy */
#define MPOL_MF_MOVE_ALL (1<<2)	/* Move every page to conform to policy */
#define MPOL_MF_LAZY	 (1<<3)	/* Modifies '_MOVE:  lazy migrate on fault */
#define MPOL_MF_INTERNAL (1<<4)	/* Internal flags start here */

#define MPOL_MF_VALID	(MPOL_MF_STRICT   | 	\
			 MPOL_MF_MOVE     | 	\
			 MPOL_MF_MOVE_ALL)

/*
 * Internal flags that share the struct mempolicy flags word with
 * "mode flags".  These flags are allocated from bit 0 up, as they
 * are never OR'ed into the mode in mempolicy API arguments.
 */
#define MPOL_F_SHARED  (1 << 0)	/* identify shared policies */
#define MPOL_F_LOCAL   (1 << 1)	/* preferred local allocation */
#define MPOL_F_REBINDING (1 << 2)	/* identify policies in rebinding */
#define MPOL_F_MOF	(1 << 3) /* this policy wants migrate on fault */
#define MPOL_F_MORON	(1 << 4) /* Migrate On pte_numa Reference On Node */


#endif /* _UAPI_BEEP_MEMPOLICY_H */
