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
#ifndef __MEMBER_DOT_H__
#define __MEMBER_DOT_H__

int dlm_ls_stop(struct dlm_ls *ls);
int dlm_ls_start(struct dlm_ls *ls);
void dlm_clear_members(struct dlm_ls *ls);
void dlm_clear_members_gone(struct dlm_ls *ls);
int dlm_recover_members(struct dlm_ls *ls, struct dlm_recover *rv,int *neg_out);
int dlm_is_removed(struct dlm_ls *ls, int nodeid);
int dlm_is_member(struct dlm_ls *ls, int nodeid);
int dlm_slots_version(struct dlm_header *h);
void dlm_slot_save(struct dlm_ls *ls, struct dlm_rcom *rc,
		   struct dlm_member *memb);
void dlm_slots_copy_out(struct dlm_ls *ls, struct dlm_rcom *rc);
int dlm_slots_copy_in(struct dlm_ls *ls);
int dlm_slots_assign(struct dlm_ls *ls, int *num_slots, int *slots_size,
		     struct dlm_slot **slots_out, uint32_t *gen_out);
void dlm_lsop_recover_done(struct dlm_ls *ls);

#endif                          /* __MEMBER_DOT_H__ */

