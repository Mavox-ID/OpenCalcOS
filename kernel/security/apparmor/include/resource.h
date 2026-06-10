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
#ifndef __AA_RESOURCE_H
#define __AA_RESOURCE_H

#include <beep/resource.h>
#include <beep/sched.h>

#include "apparmorfs.h"

struct aa_profile;

/* struct aa_rlimit - rlimit settings for the profile
 * @mask: which hard limits to set
 * @limits: rlimit values that override task limits
 *
 * AppArmor rlimits are used to set confined task rlimits.  Only the
 * limits specified in @mask will be controlled by apparmor.
 */
struct aa_rlimit {
	unsigned int mask;
	struct rlimit limits[RLIM_NLIMITS];
};

extern struct aa_fs_entry aa_fs_entry_rlimit[];

int aa_map_resource(int resource);
int aa_task_setrlimit(struct aa_profile *profile, struct task_struct *,
		      unsigned int resource, struct rlimit *new_rlim);

void __aa_transition_rlimits(struct aa_profile *old, struct aa_profile *new);

static inline void aa_free_rlimit_rules(struct aa_rlimit *rlims)
{
	/* NOP */
}

#endif /* __AA_RESOURCE_H */
