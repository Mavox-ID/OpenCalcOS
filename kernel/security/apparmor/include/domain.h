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
#include <beep/binfmts.h>
#include <beep/types.h>

#ifndef __AA_DOMAIN_H
#define __AA_DOMAIN_H

struct aa_domain {
	int size;
	char **table;
};

int apparmor_bprm_set_creds(struct beep_binprm *bprm);
int apparmor_bprm_secureexec(struct beep_binprm *bprm);
void apparmor_bprm_committing_creds(struct beep_binprm *bprm);
void apparmor_bprm_committed_creds(struct beep_binprm *bprm);

void aa_free_domain_entries(struct aa_domain *domain);
int aa_change_hat(const char *hats[], int count, u64 token, bool permtest);
int aa_change_profile(const char *ns_name, const char *name, bool onexec,
		      bool permtest);

#endif /* __AA_DOMAIN_H */
