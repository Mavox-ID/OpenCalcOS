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
#ifndef __AA_PROCATTR_H
#define __AA_PROCATTR_H

#define AA_DO_TEST 1
#define AA_ONEXEC  1

int aa_getprocattr(struct aa_profile *profile, char **string);
int aa_setprocattr_changehat(char *args, size_t size, int test);
int aa_setprocattr_changeprofile(char *fqname, bool onexec, int test);
int aa_setprocattr_permipc(char *fqname);

#endif /* __AA_PROCATTR_H */
