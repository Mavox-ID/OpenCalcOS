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
#ifndef _BEEP_DNS_RESOLVER_H
#define _BEEP_DNS_RESOLVER_H

#ifdef __KERNEL__

extern int dns_query(const char *type, const char *name, size_t namelen,
		     const char *options, char **_result, time_t *_expiry);

#endif /* KERNEL */

#endif /* _BEEP_DNS_RESOLVER_H */
