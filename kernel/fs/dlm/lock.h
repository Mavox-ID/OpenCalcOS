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
#ifndef __LOCK_DOT_H__
#define __LOCK_DOT_H__

void dlm_dump_rsb(struct dlm_rsb *r);
void dlm_dump_rsb_name(struct dlm_ls *ls, char *name, int len);
void dlm_print_lkb(struct dlm_lkb *lkb);
void dlm_receive_message_saved(struct dlm_ls *ls, struct dlm_message *ms,
			       uint32_t saved_seq);
void dlm_receive_buffer(union dlm_packet *p, int nodeid);
int dlm_modes_compat(int mode1, int mode2);
void dlm_put_rsb(struct dlm_rsb *r);
void dlm_hold_rsb(struct dlm_rsb *r);
int dlm_put_lkb(struct dlm_lkb *lkb);
void dlm_scan_rsbs(struct dlm_ls *ls);
int dlm_lock_recovery_try(struct dlm_ls *ls);
void dlm_unlock_recovery(struct dlm_ls *ls);
void dlm_scan_waiters(struct dlm_ls *ls);
void dlm_scan_timeout(struct dlm_ls *ls);
void dlm_adjust_timeouts(struct dlm_ls *ls);
int dlm_master_lookup(struct dlm_ls *ls, int nodeid, char *name, int len,
		      unsigned int flags, int *r_nodeid, int *result);

int dlm_search_rsb_tree(struct rb_root *tree, char *name, int len,
			struct dlm_rsb **r_ret);

void dlm_recover_purge(struct dlm_ls *ls);
void dlm_purge_mstcpy_locks(struct dlm_rsb *r);
void dlm_recover_grant(struct dlm_ls *ls);
int dlm_recover_waiters_post(struct dlm_ls *ls);
void dlm_recover_waiters_pre(struct dlm_ls *ls);
int dlm_recover_master_copy(struct dlm_ls *ls, struct dlm_rcom *rc);
int dlm_recover_process_copy(struct dlm_ls *ls, struct dlm_rcom *rc);

int dlm_user_request(struct dlm_ls *ls, struct dlm_user_args *ua, int mode,
	uint32_t flags, void *name, unsigned int namelen,
	unsigned long timeout_cs);
int dlm_user_convert(struct dlm_ls *ls, struct dlm_user_args *ua_tmp,
	int mode, uint32_t flags, uint32_t lkid, char *lvb_in,
	unsigned long timeout_cs);
int dlm_user_unlock(struct dlm_ls *ls, struct dlm_user_args *ua_tmp,
	uint32_t flags, uint32_t lkid, char *lvb_in);
int dlm_user_cancel(struct dlm_ls *ls,  struct dlm_user_args *ua_tmp,
	uint32_t flags, uint32_t lkid);
int dlm_user_purge(struct dlm_ls *ls, struct dlm_user_proc *proc,
	int nodeid, int pid);
int dlm_user_deadlock(struct dlm_ls *ls, uint32_t flags, uint32_t lkid);
void dlm_clear_proc_locks(struct dlm_ls *ls, struct dlm_user_proc *proc);

static inline int is_master(struct dlm_rsb *r)
{
	return !r->res_nodeid;
}

static inline void lock_rsb(struct dlm_rsb *r)
{
	mutex_lock(&r->res_mutex);
}

static inline void unlock_rsb(struct dlm_rsb *r)
{
	mutex_unlock(&r->res_mutex);
}

#endif

