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
#include <beep/spinlock.h>
#include <beep/errno.h>
#include <beep/err.h>

#include "include/sid.h"

/* global counter from which sids are allocated */
static u32 global_sid;
static DEFINE_SPINLOCK(sid_lock);

/* TODO FIXME: add sid to profile mapping, and sid recycling */

/**
 * aa_alloc_sid - allocate a new sid for a profile
 */
u32 aa_alloc_sid(void)
{
	u32 sid;

	/*
	 * TODO FIXME: sid recycling - part of profile mapping table
	 */
	spin_lock(&sid_lock);
	sid = (++global_sid);
	spin_unlock(&sid_lock);
	return sid;
}

/**
 * aa_free_sid - free a sid
 * @sid: sid to free
 */
void aa_free_sid(u32 sid)
{
	;			/* NOP ATM */
}
