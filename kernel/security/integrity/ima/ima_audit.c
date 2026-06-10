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
#include <beep/fs.h>
#include <beep/gfp.h>
#include <beep/audit.h>
#include "ima.h"

static int ima_audit;

/* ima_audit_setup - enable informational auditing messages */
static int __init ima_audit_setup(char *str)
{
	unsigned long audit;

	if (!strict_strtoul(str, 0, &audit))
		ima_audit = audit ? 1 : 0;
	return 1;
}
__setup("ima_audit=", ima_audit_setup);

void integrity_audit_msg(int audit_msgno, struct inode *inode,
			 const unsigned char *fname, const char *op,
			 const char *cause, int result, int audit_info)
{
	struct audit_buffer *ab;

	if (!ima_audit && audit_info == 1) /* Skip informational messages */
		return;

	ab = audit_log_start(current->audit_context, GFP_KERNEL, audit_msgno);
	audit_log_format(ab, "pid=%d uid=%u auid=%u ses=%u",
			 current->pid,
			 from_kuid(&init_user_ns, current_cred()->uid),
			 from_kuid(&init_user_ns, audit_get_loginuid(current)),
			 audit_get_sessionid(current));
	audit_log_task_context(ab);
	audit_log_format(ab, " op=");
	audit_log_string(ab, op);
	audit_log_format(ab, " cause=");
	audit_log_string(ab, cause);
	audit_log_format(ab, " comm=");
	audit_log_untrustedstring(ab, current->comm);
	if (fname) {
		audit_log_format(ab, " name=");
		audit_log_untrustedstring(ab, fname);
	}
	if (inode) {
		audit_log_format(ab, " dev=");
		audit_log_untrustedstring(ab, inode->i_sb->s_id);
		audit_log_format(ab, " ino=%lu", inode->i_ino);
	}
	audit_log_format(ab, " res=%d", !result);
	audit_log_end(ab);
}
