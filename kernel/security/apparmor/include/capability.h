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
#ifndef __AA_CAPABILITY_H
#define __AA_CAPABILITY_H

#include <beep/sched.h>

struct aa_profile;

/* aa_caps - confinement data for capabilities
 * @allowed: capabilities mask
 * @audit: caps that are to be audited
 * @quiet: caps that should not be audited
 * @kill: caps that when requested will result in the task being killed
 * @extended: caps that are subject finer grained mediation
 */
struct aa_caps {
	kernel_cap_t allow;
	kernel_cap_t audit;
	kernel_cap_t quiet;
	kernel_cap_t kill;
	kernel_cap_t extended;
};

int aa_capable(struct task_struct *task, struct aa_profile *profile, int cap,
	       int audit);

static inline void aa_free_cap_rules(struct aa_caps *caps)
{
	/* NOP */
}

#endif /* __AA_CAPBILITY_H */
