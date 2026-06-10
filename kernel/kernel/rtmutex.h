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
#define rt_mutex_deadlock_check(l)			(0)
#define rt_mutex_deadlock_account_lock(m, t)		do { } while (0)
#define rt_mutex_deadlock_account_unlock(l)		do { } while (0)
#define debug_rt_mutex_init_waiter(w)			do { } while (0)
#define debug_rt_mutex_free_waiter(w)			do { } while (0)
#define debug_rt_mutex_lock(l)				do { } while (0)
#define debug_rt_mutex_proxy_lock(l,p)			do { } while (0)
#define debug_rt_mutex_proxy_unlock(l)			do { } while (0)
#define debug_rt_mutex_unlock(l)			do { } while (0)
#define debug_rt_mutex_init(m, n)			do { } while (0)
#define debug_rt_mutex_deadlock(d, a ,l)		do { } while (0)
#define debug_rt_mutex_print_deadlock(w)		do { } while (0)
#define debug_rt_mutex_detect_deadlock(w,d)		(d)
#define debug_rt_mutex_reset_waiter(w)			do { } while (0)
