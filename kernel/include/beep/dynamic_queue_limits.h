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
#ifndef _BEEP_DQL_H
#define _BEEP_DQL_H

#ifdef __KERNEL__

struct dql {
	/* Fields accessed in enqueue path (dql_queued) */
	unsigned int	num_queued;		/* Total ever queued */
	unsigned int	adj_limit;		/* limit + num_completed */
	unsigned int	last_obj_cnt;		/* Count at last queuing */

	/* Fields accessed only by completion path (dql_completed) */

	unsigned int	limit ____cacheline_aligned_in_smp; /* Current limit */
	unsigned int	num_completed;		/* Total ever completed */

	unsigned int	prev_ovlimit;		/* Previous over limit */
	unsigned int	prev_num_queued;	/* Previous queue total */
	unsigned int	prev_last_obj_cnt;	/* Previous queuing cnt */

	unsigned int	lowest_slack;		/* Lowest slack found */
	unsigned long	slack_start_time;	/* Time slacks seen */

	/* Configuration */
	unsigned int	max_limit;		/* Max limit */
	unsigned int	min_limit;		/* Minimum limit */
	unsigned int	slack_hold_time;	/* Time to measure slack */
};

/* Set some static maximums */
#define DQL_MAX_OBJECT (UINT_MAX / 16)
#define DQL_MAX_LIMIT ((UINT_MAX / 2) - DQL_MAX_OBJECT)

/*
 * Record number of objects queued. Assumes that caller has already checked
 * availability in the queue with dql_avail.
 */
static inline void dql_queued(struct dql *dql, unsigned int count)
{
	BUG_ON(count > DQL_MAX_OBJECT);

	dql->num_queued += count;
	dql->last_obj_cnt = count;
}

/* Returns how many objects can be queued, < 0 indicates over limit. */
static inline int dql_avail(const struct dql *dql)
{
	return dql->adj_limit - dql->num_queued;
}

/* Record number of completed objects and recalculate the limit. */
void dql_completed(struct dql *dql, unsigned int count);

/* Reset dql state */
void dql_reset(struct dql *dql);

/* Initialize dql state */
int dql_init(struct dql *dql, unsigned hold_time);

#endif /* _KERNEL_ */

#endif /* _BEEP_DQL_H */
