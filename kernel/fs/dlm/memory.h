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
#ifndef __MEMORY_DOT_H__
#define __MEMORY_DOT_H__

int dlm_memory_init(void);
void dlm_memory_exit(void);
struct dlm_rsb *dlm_allocate_rsb(struct dlm_ls *ls);
void dlm_free_rsb(struct dlm_rsb *r);
struct dlm_lkb *dlm_allocate_lkb(struct dlm_ls *ls);
void dlm_free_lkb(struct dlm_lkb *l);
char *dlm_allocate_lvb(struct dlm_ls *ls);
void dlm_free_lvb(char *l);

#endif		/* __MEMORY_DOT_H__ */

