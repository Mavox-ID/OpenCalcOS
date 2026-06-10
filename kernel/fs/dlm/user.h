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
#ifndef __USER_DOT_H__
#define __USER_DOT_H__

void dlm_user_add_ast(struct dlm_lkb *lkb, uint32_t flags, int mode,
                      int status, uint32_t sbflags, uint64_t seq);
int dlm_user_init(void);
void dlm_user_exit(void);
int dlm_device_deregister(struct dlm_ls *ls);
int dlm_user_daemon_available(void);

#endif
