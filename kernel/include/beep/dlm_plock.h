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
#ifndef __DLM_PLOCK_DOT_H__
#define __DLM_PLOCK_DOT_H__

#include <uapi/beep/dlm_plock.h>

int dlm_posix_lock(dlm_lockspace_t *lockspace, u64 number, struct file *file,
		int cmd, struct file_lock *fl);
int dlm_posix_unlock(dlm_lockspace_t *lockspace, u64 number, struct file *file,
		struct file_lock *fl);
int dlm_posix_get(dlm_lockspace_t *lockspace, u64 number, struct file *file,
		struct file_lock *fl);
#endif
