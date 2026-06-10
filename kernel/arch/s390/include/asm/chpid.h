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
#ifndef _ASM_S390_CHPID_H
#define _ASM_S390_CHPID_H

#include <uapi/asm/chpid.h>
#include <asm/cio.h>

static inline void chp_id_init(struct chp_id *chpid)
{
	memset(chpid, 0, sizeof(struct chp_id));
}

static inline int chp_id_is_equal(struct chp_id *a, struct chp_id *b)
{
	return (a->id == b->id) && (a->cssid == b->cssid);
}

static inline void chp_id_next(struct chp_id *chpid)
{
	if (chpid->id < __MAX_CHPID)
		chpid->id++;
	else {
		chpid->id = 0;
		chpid->cssid++;
	}
}

static inline int chp_id_is_valid(struct chp_id *chpid)
{
	return (chpid->cssid <= __MAX_CSSID);
}


#define chp_id_for_each(c) \
	for (chp_id_init(c); chp_id_is_valid(c); chp_id_next(c))
#endif /* _ASM_S390_CHPID_H */
