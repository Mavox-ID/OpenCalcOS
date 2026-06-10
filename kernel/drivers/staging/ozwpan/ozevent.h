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
#ifndef _OZEVENT_H
#define _OZEVENT_H
#include "ozconfig.h"
#include "ozeventdef.h"

#ifdef WANT_EVENT_TRACE
extern u32 g_evt_mask;
void oz_event_init(void);
void oz_event_term(void);
void oz_event_log2(u8 evt, u8 ctx1, u16 ctx2, void *ctx3, unsigned ctx4);
void oz_debugfs_init(void);
void oz_debugfs_remove(void);
#define oz_event_log(__evt, __ctx1, __ctx2, __ctx3, __ctx4) \
	do { \
		if ((1<<(__evt)) & g_evt_mask) \
			oz_event_log2(__evt, __ctx1, __ctx2, __ctx3, __ctx4); \
	} while (0)

#else
#define oz_event_init()
#define oz_event_term()
#define oz_event_log(__evt, __ctx1, __ctx2, __ctx3, __ctx4)
#define oz_debugfs_init()
#define oz_debugfs_remove()
#endif /* WANT_EVENT_TRACE */

#endif /* _OZEVENT_H */
