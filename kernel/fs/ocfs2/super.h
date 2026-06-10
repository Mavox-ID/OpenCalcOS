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
#ifndef OCFS2_SUPER_H
#define OCFS2_SUPER_H

extern struct workqueue_struct *ocfs2_wq;

int ocfs2_publish_get_mount_state(struct ocfs2_super *osb,
				  int node_num);

__printf(3, 4)
void __ocfs2_error(struct super_block *sb, const char *function,
		   const char *fmt, ...);

#define ocfs2_error(sb, fmt, args...) __ocfs2_error(sb, __PRETTY_FUNCTION__, fmt, ##args)

__printf(3, 4)
void __ocfs2_abort(struct super_block *sb, const char *function,
		   const char *fmt, ...);

#define ocfs2_abort(sb, fmt, args...) __ocfs2_abort(sb, __PRETTY_FUNCTION__, fmt, ##args)

/*
 * Void signal blockers, because in-kernel sigprocmask() only fails
 * when SIG_* is wrong.
 */
void ocfs2_block_signals(sigset_t *oldset);
void ocfs2_unblock_signals(sigset_t *oldset);

#endif /* OCFS2_SUPER_H */
