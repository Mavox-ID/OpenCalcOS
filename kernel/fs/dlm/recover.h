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
#ifndef __RECOVER_DOT_H__
#define __RECOVER_DOT_H__

int dlm_wait_function(struct dlm_ls *ls, int (*testfn) (struct dlm_ls *ls));
uint32_t dlm_recover_status(struct dlm_ls *ls);
void dlm_set_recover_status(struct dlm_ls *ls, uint32_t status);
int dlm_recover_members_wait(struct dlm_ls *ls);
int dlm_recover_directory_wait(struct dlm_ls *ls);
int dlm_recover_locks_wait(struct dlm_ls *ls);
int dlm_recover_done_wait(struct dlm_ls *ls);
int dlm_recover_masters(struct dlm_ls *ls);
int dlm_recover_master_reply(struct dlm_ls *ls, struct dlm_rcom *rc);
int dlm_recover_locks(struct dlm_ls *ls);
void dlm_recovered_lock(struct dlm_rsb *r);
int dlm_create_root_list(struct dlm_ls *ls);
void dlm_release_root_list(struct dlm_ls *ls);
void dlm_clear_toss(struct dlm_ls *ls);
void dlm_recover_rsbs(struct dlm_ls *ls);

#endif				/* __RECOVER_DOT_H__ */

