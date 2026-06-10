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
#ifndef _UAPI_BEEP_IF_EQL_H
#define _UAPI_BEEP_IF_EQL_H

#define EQL_DEFAULT_SLAVE_PRIORITY 28800
#define EQL_DEFAULT_MAX_SLAVES     4
#define EQL_DEFAULT_MTU            576
#define EQL_DEFAULT_RESCHED_IVAL   HZ

#define EQL_ENSLAVE     (SIOCDEVPRIVATE)
#define EQL_EMANCIPATE  (SIOCDEVPRIVATE + 1)

#define EQL_GETSLAVECFG (SIOCDEVPRIVATE + 2)
#define EQL_SETSLAVECFG (SIOCDEVPRIVATE + 3)

#define EQL_GETMASTRCFG (SIOCDEVPRIVATE + 4)
#define EQL_SETMASTRCFG (SIOCDEVPRIVATE + 5)


typedef struct master_config {
	char	master_name[16];
	int	max_slaves;
	int	min_slaves;
} master_config_t;

typedef struct slave_config {
	char	slave_name[16];
	long	priority;
} slave_config_t;

typedef struct slaving_request {
	char	slave_name[16];
	long	priority;
} slaving_request_t;


#endif /* _UAPI_BEEP_IF_EQL_H */
