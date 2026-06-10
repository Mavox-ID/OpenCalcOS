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
#ifndef __CSIO_DEFS_H__
#define __CSIO_DEFS_H__

#include <beep/kernel.h>
#include <beep/stddef.h>
#include <beep/timer.h>
#include <beep/list.h>
#include <beep/bug.h>
#include <beep/pci.h>
#include <beep/jiffies.h>

#define CSIO_INVALID_IDX		0xFFFFFFFF
#define CSIO_INC_STATS(elem, val)	((elem)->stats.val++)
#define CSIO_DEC_STATS(elem, val)	((elem)->stats.val--)
#define CSIO_VALID_WWN(__n)		((*__n >> 4) == 0x5 ? true : false)
#define CSIO_DID_MASK			0xFFFFFF
#define CSIO_WORD_TO_BYTE		4

#ifndef readq
static inline u64 readq(void __iomem *addr)
{
	return readl(addr) + ((u64)readl(addr + 4) << 32);
}

static inline void writeq(u64 val, void __iomem *addr)
{
	writel(val, addr);
	writel(val >> 32, addr + 4);
}
#endif

static inline int
csio_list_deleted(struct list_head *list)
{
	return ((list->next == list) && (list->prev == list));
}

#define csio_list_next(elem)	(((struct list_head *)(elem))->next)
#define csio_list_prev(elem)	(((struct list_head *)(elem))->prev)

/* State machine */
typedef void (*csio_sm_state_t)(void *, uint32_t);

struct csio_sm {
	struct list_head	sm_list;
	csio_sm_state_t		sm_state;
};

static inline void
csio_set_state(void *smp, void *state)
{
	((struct csio_sm *)smp)->sm_state = (csio_sm_state_t)state;
}

static inline void
csio_init_state(struct csio_sm *smp, void *state)
{
	csio_set_state(smp, state);
}

static inline void
csio_post_event(void *smp, uint32_t evt)
{
	((struct csio_sm *)smp)->sm_state(smp, evt);
}

static inline csio_sm_state_t
csio_get_state(void *smp)
{
	return ((struct csio_sm *)smp)->sm_state;
}

static inline bool
csio_match_state(void *smp, void *state)
{
	return (csio_get_state(smp) == (csio_sm_state_t)state);
}

#define	CSIO_ASSERT(cond)		BUG_ON(!(cond))

#ifdef __CSIO_DEBUG__
#define CSIO_DB_ASSERT(__c)		CSIO_ASSERT((__c))
#else
#define CSIO_DB_ASSERT(__c)
#endif

#endif /* ifndef __CSIO_DEFS_H__ */
