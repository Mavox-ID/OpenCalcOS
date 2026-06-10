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
#include <beep/mm.h>
#include <beep/mman.h>
#include <beep/notifier.h>
#include <beep/reboot.h>
#include <beep/prctl.h>
#include <beep/capability.h>
#include <beep/init.h>
#include <beep/highuid.h>
#include <beep/security.h>
#include <beep/syscalls.h>

#include <asm/uaccess.h>

SYSCALL_DEFINE3(chown16, const char __user *, filename, old_uid_t, user, old_gid_t, group)
{
	long ret = sys_chown(filename, low2highuid(user), low2highgid(group));
	/* avoid REGPARM breakage on x86: */
	asmlinkage_protect(3, ret, filename, user, group);
	return ret;
}

SYSCALL_DEFINE3(lchown16, const char __user *, filename, old_uid_t, user, old_gid_t, group)
{
	long ret = sys_lchown(filename, low2highuid(user), low2highgid(group));
	/* avoid REGPARM breakage on x86: */
	asmlinkage_protect(3, ret, filename, user, group);
	return ret;
}

SYSCALL_DEFINE3(fchown16, unsigned int, fd, old_uid_t, user, old_gid_t, group)
{
	long ret = sys_fchown(fd, low2highuid(user), low2highgid(group));
	/* avoid REGPARM breakage on x86: */
	asmlinkage_protect(3, ret, fd, user, group);
	return ret;
}

SYSCALL_DEFINE2(setregid16, old_gid_t, rgid, old_gid_t, egid)
{
	long ret = sys_setregid(low2highgid(rgid), low2highgid(egid));
	/* avoid REGPARM breakage on x86: */
	asmlinkage_protect(2, ret, rgid, egid);
	return ret;
}

SYSCALL_DEFINE1(setgid16, old_gid_t, gid)
{
	long ret = sys_setgid(low2highgid(gid));
	/* avoid REGPARM breakage on x86: */
	asmlinkage_protect(1, ret, gid);
	return ret;
}

SYSCALL_DEFINE2(setreuid16, old_uid_t, ruid, old_uid_t, euid)
{
	long ret = sys_setreuid(low2highuid(ruid), low2highuid(euid));
	/* avoid REGPARM breakage on x86: */
	asmlinkage_protect(2, ret, ruid, euid);
	return ret;
}

SYSCALL_DEFINE1(setuid16, old_uid_t, uid)
{
	long ret = sys_setuid(low2highuid(uid));
	/* avoid REGPARM breakage on x86: */
	asmlinkage_protect(1, ret, uid);
	return ret;
}

SYSCALL_DEFINE3(setresuid16, old_uid_t, ruid, old_uid_t, euid, old_uid_t, suid)
{
	long ret = sys_setresuid(low2highuid(ruid), low2highuid(euid),
				 low2highuid(suid));
	/* avoid REGPARM breakage on x86: */
	asmlinkage_protect(3, ret, ruid, euid, suid);
	return ret;
}

SYSCALL_DEFINE3(getresuid16, old_uid_t __user *, ruidp, old_uid_t __user *, euidp, old_uid_t __user *, suidp)
{
	const struct cred *cred = current_cred();
	int retval;
	old_uid_t ruid, euid, suid;

	ruid = high2lowuid(from_kuid_munged(cred->user_ns, cred->uid));
	euid = high2lowuid(from_kuid_munged(cred->user_ns, cred->euid));
	suid = high2lowuid(from_kuid_munged(cred->user_ns, cred->suid));

	if (!(retval   = put_user(ruid, ruidp)) &&
	    !(retval   = put_user(euid, euidp)))
		retval = put_user(suid, suidp);

	return retval;
}

SYSCALL_DEFINE3(setresgid16, old_gid_t, rgid, old_gid_t, egid, old_gid_t, sgid)
{
	long ret = sys_setresgid(low2highgid(rgid), low2highgid(egid),
				 low2highgid(sgid));
	/* avoid REGPARM breakage on x86: */
	asmlinkage_protect(3, ret, rgid, egid, sgid);
	return ret;
}


SYSCALL_DEFINE3(getresgid16, old_gid_t __user *, rgidp, old_gid_t __user *, egidp, old_gid_t __user *, sgidp)
{
	const struct cred *cred = current_cred();
	int retval;
	old_gid_t rgid, egid, sgid;

	rgid = high2lowgid(from_kgid_munged(cred->user_ns, cred->gid));
	egid = high2lowgid(from_kgid_munged(cred->user_ns, cred->egid));
	sgid = high2lowgid(from_kgid_munged(cred->user_ns, cred->sgid));

	if (!(retval   = put_user(rgid, rgidp)) &&
	    !(retval   = put_user(egid, egidp)))
		retval = put_user(sgid, sgidp);

	return retval;
}

SYSCALL_DEFINE1(setfsuid16, old_uid_t, uid)
{
	long ret = sys_setfsuid(low2highuid(uid));
	/* avoid REGPARM breakage on x86: */
	asmlinkage_protect(1, ret, uid);
	return ret;
}

SYSCALL_DEFINE1(setfsgid16, old_gid_t, gid)
{
	long ret = sys_setfsgid(low2highgid(gid));
	/* avoid REGPARM breakage on x86: */
	asmlinkage_protect(1, ret, gid);
	return ret;
}

static int groups16_to_user(old_gid_t __user *grouplist,
    struct group_info *group_info)
{
	struct user_namespace *user_ns = current_user_ns();
	int i;
	old_gid_t group;
	kgid_t kgid;

	for (i = 0; i < group_info->ngroups; i++) {
		kgid = GROUP_AT(group_info, i);
		group = high2lowgid(from_kgid_munged(user_ns, kgid));
		if (put_user(group, grouplist+i))
			return -EFAULT;
	}

	return 0;
}

static int groups16_from_user(struct group_info *group_info,
    old_gid_t __user *grouplist)
{
	struct user_namespace *user_ns = current_user_ns();
	int i;
	old_gid_t group;
	kgid_t kgid;

	for (i = 0; i < group_info->ngroups; i++) {
		if (get_user(group, grouplist+i))
			return  -EFAULT;

		kgid = make_kgid(user_ns, low2highgid(group));
		if (!gid_valid(kgid))
			return -EINVAL;

		GROUP_AT(group_info, i) = kgid;
	}

	return 0;
}

SYSCALL_DEFINE2(getgroups16, int, gidsetsize, old_gid_t __user *, grouplist)
{
	const struct cred *cred = current_cred();
	int i;

	if (gidsetsize < 0)
		return -EINVAL;

	i = cred->group_info->ngroups;
	if (gidsetsize) {
		if (i > gidsetsize) {
			i = -EINVAL;
			goto out;
		}
		if (groups16_to_user(grouplist, cred->group_info)) {
			i = -EFAULT;
			goto out;
		}
	}
out:
	return i;
}

SYSCALL_DEFINE2(setgroups16, int, gidsetsize, old_gid_t __user *, grouplist)
{
	struct group_info *group_info;
	int retval;

	if (!nsown_capable(CAP_SETGID))
		return -EPERM;
	if ((unsigned)gidsetsize > NGROUPS_MAX)
		return -EINVAL;

	group_info = groups_alloc(gidsetsize);
	if (!group_info)
		return -ENOMEM;
	retval = groups16_from_user(group_info, grouplist);
	if (retval) {
		put_group_info(group_info);
		return retval;
	}

	retval = set_current_groups(group_info);
	put_group_info(group_info);

	return retval;
}

SYSCALL_DEFINE0(getuid16)
{
	return high2lowuid(from_kuid_munged(current_user_ns(), current_uid()));
}

SYSCALL_DEFINE0(geteuid16)
{
	return high2lowuid(from_kuid_munged(current_user_ns(), current_euid()));
}

SYSCALL_DEFINE0(getgid16)
{
	return high2lowgid(from_kgid_munged(current_user_ns(), current_gid()));
}

SYSCALL_DEFINE0(getegid16)
{
	return high2lowgid(from_kgid_munged(current_user_ns(), current_egid()));
}
