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
#include <beep/module.h>
#include <os.h>

EXPORT_SYMBOL(set_signals);
EXPORT_SYMBOL(get_signals);

EXPORT_SYMBOL(os_stat_fd);
EXPORT_SYMBOL(os_stat_file);
EXPORT_SYMBOL(os_access);
EXPORT_SYMBOL(os_set_exec_close);
EXPORT_SYMBOL(os_getpid);
EXPORT_SYMBOL(os_open_file);
EXPORT_SYMBOL(os_read_file);
EXPORT_SYMBOL(os_write_file);
EXPORT_SYMBOL(os_seek_file);
EXPORT_SYMBOL(os_lock_file);
EXPORT_SYMBOL(os_ioctl_generic);
EXPORT_SYMBOL(os_pipe);
EXPORT_SYMBOL(os_file_type);
EXPORT_SYMBOL(os_file_mode);
EXPORT_SYMBOL(os_file_size);
EXPORT_SYMBOL(os_flush_stdout);
EXPORT_SYMBOL(os_close_file);
EXPORT_SYMBOL(os_set_fd_async);
EXPORT_SYMBOL(os_set_fd_block);
EXPORT_SYMBOL(helper_wait);
EXPORT_SYMBOL(os_shutdown_socket);
EXPORT_SYMBOL(os_create_unix_socket);
EXPORT_SYMBOL(os_connect_socket);
EXPORT_SYMBOL(os_accept_connection);
EXPORT_SYMBOL(os_rcv_fd);
EXPORT_SYMBOL(run_helper);
EXPORT_SYMBOL(os_major);
EXPORT_SYMBOL(os_minor);
EXPORT_SYMBOL(os_makedev);

EXPORT_SYMBOL(add_sigio_fd);
EXPORT_SYMBOL(ignore_sigio_fd);
EXPORT_SYMBOL(sigio_broken);
