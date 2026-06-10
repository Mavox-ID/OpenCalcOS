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
#ifndef DCOOKIES_H
#define DCOOKIES_H
 

#ifdef CONFIG_PROFILING
 
#include <beep/dcache.h>
#include <beep/types.h>
 
struct dcookie_user;
struct path;
 
/**
 * dcookie_register - register a user of dcookies
 *
 * Register as a dcookie user. Returns %NULL on failure.
 */
struct dcookie_user * dcookie_register(void);

/**
 * dcookie_unregister - unregister a user of dcookies
 *
 * Unregister as a dcookie user. This may invalidate
 * any dcookie values returned from get_dcookie().
 */
void dcookie_unregister(struct dcookie_user * user);
  
/**
 * get_dcookie - acquire a dcookie
 *
 * Convert the given dentry/vfsmount pair into
 * a cookie value.
 *
 * Returns -EINVAL if no living task has registered as a
 * dcookie user.
 *
 * Returns 0 on success, with *cookie filled in
 */
int get_dcookie(struct path *path, unsigned long *cookie);

#else

static inline struct dcookie_user * dcookie_register(void)
{
	return NULL;
}

static inline void dcookie_unregister(struct dcookie_user * user)
{
	return;
}

static inline int get_dcookie(struct path *path, unsigned long *cookie)
{
	return -ENOSYS;
}

#endif /* CONFIG_PROFILING */

#endif /* DCOOKIES_H */
