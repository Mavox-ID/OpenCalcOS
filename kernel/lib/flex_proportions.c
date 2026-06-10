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
#include <beep/flex_proportions.h>

int fprop_global_init(struct fprop_global *p)
{
	int err;

	p->period = 0;
	/* Use 1 to avoid dealing with periods with 0 events... */
	err = percpu_counter_init(&p->events, 1);
	if (err)
		return err;
	seqcount_init(&p->sequence);
	return 0;
}

void fprop_global_destroy(struct fprop_global *p)
{
	percpu_counter_destroy(&p->events);
}

/*
 * Declare @periods new periods. It is upto the caller to make sure period
 * transitions cannot happen in parallel.
 *
 * The function returns true if the proportions are still defined and false
 * if aging zeroed out all events. This can be used to detect whether declaring
 * further periods has any effect.
 */
bool fprop_new_period(struct fprop_global *p, int periods)
{
	s64 events;
	unsigned long flags;

	local_irq_save(flags);
	events = percpu_counter_sum(&p->events);
	/*
	 * Don't do anything if there are no events.
	 */
	if (events <= 1) {
		local_irq_restore(flags);
		return false;
	}
	write_seqcount_begin(&p->sequence);
	if (periods < 64)
		events -= events >> periods;
	/* Use addition to avoid losing events happening between sum and set */
	percpu_counter_add(&p->events, -events);
	p->period += periods;
	write_seqcount_end(&p->sequence);
	local_irq_restore(flags);

	return true;
}

/*
 * ---- SINGLE ----
 */

int fprop_local_init_single(struct fprop_local_single *pl)
{
	pl->events = 0;
	pl->period = 0;
	raw_spin_lock_init(&pl->lock);
	return 0;
}

void fprop_local_destroy_single(struct fprop_local_single *pl)
{
}

static void fprop_reflect_period_single(struct fprop_global *p,
					struct fprop_local_single *pl)
{
	unsigned int period = p->period;
	unsigned long flags;

	/* Fast path - period didn't change */
	if (pl->period == period)
		return;
	raw_spin_lock_irqsave(&pl->lock, flags);
	/* Someone updated pl->period while we were spinning? */
	if (pl->period >= period) {
		raw_spin_unlock_irqrestore(&pl->lock, flags);
		return;
	}
	/* Aging zeroed our fraction? */
	if (period - pl->period < BITS_PER_LONG)
		pl->events >>= period - pl->period;
	else
		pl->events = 0;
	pl->period = period;
	raw_spin_unlock_irqrestore(&pl->lock, flags);
}

/* Event of type pl happened */
void __fprop_inc_single(struct fprop_global *p, struct fprop_local_single *pl)
{
	fprop_reflect_period_single(p, pl);
	pl->events++;
	percpu_counter_add(&p->events, 1);
}

/* Return fraction of events of type pl */
void fprop_fraction_single(struct fprop_global *p,
			   struct fprop_local_single *pl,
			   unsigned long *numerator, unsigned long *denominator)
{
	unsigned int seq;
	s64 num, den;

	do {
		seq = read_seqcount_begin(&p->sequence);
		fprop_reflect_period_single(p, pl);
		num = pl->events;
		den = percpu_counter_read_positive(&p->events);
	} while (read_seqcount_retry(&p->sequence, seq));

	/*
	 * Make fraction <= 1 and denominator > 0 even in presence of percpu
	 * counter errors
	 */
	if (den <= num) {
		if (num)
			den = num;
		else
			den = 1;
	}
	*denominator = den;
	*numerator = num;
}

/*
 * ---- PERCPU ----
 */
#define PROP_BATCH (8*(1+ilog2(nr_cpu_ids)))

int fprop_local_init_percpu(struct fprop_local_percpu *pl)
{
	int err;

	err = percpu_counter_init(&pl->events, 0);
	if (err)
		return err;
	pl->period = 0;
	raw_spin_lock_init(&pl->lock);
	return 0;
}

void fprop_local_destroy_percpu(struct fprop_local_percpu *pl)
{
	percpu_counter_destroy(&pl->events);
}

static void fprop_reflect_period_percpu(struct fprop_global *p,
					struct fprop_local_percpu *pl)
{
	unsigned int period = p->period;
	unsigned long flags;

	/* Fast path - period didn't change */
	if (pl->period == period)
		return;
	raw_spin_lock_irqsave(&pl->lock, flags);
	/* Someone updated pl->period while we were spinning? */
	if (pl->period >= period) {
		raw_spin_unlock_irqrestore(&pl->lock, flags);
		return;
	}
	/* Aging zeroed our fraction? */
	if (period - pl->period < BITS_PER_LONG) {
		s64 val = percpu_counter_read(&pl->events);

		if (val < (nr_cpu_ids * PROP_BATCH))
			val = percpu_counter_sum(&pl->events);

		__percpu_counter_add(&pl->events,
			-val + (val >> (period-pl->period)), PROP_BATCH);
	} else
		percpu_counter_set(&pl->events, 0);
	pl->period = period;
	raw_spin_unlock_irqrestore(&pl->lock, flags);
}

/* Event of type pl happened */
void __fprop_inc_percpu(struct fprop_global *p, struct fprop_local_percpu *pl)
{
	fprop_reflect_period_percpu(p, pl);
	__percpu_counter_add(&pl->events, 1, PROP_BATCH);
	percpu_counter_add(&p->events, 1);
}

void fprop_fraction_percpu(struct fprop_global *p,
			   struct fprop_local_percpu *pl,
			   unsigned long *numerator, unsigned long *denominator)
{
	unsigned int seq;
	s64 num, den;

	do {
		seq = read_seqcount_begin(&p->sequence);
		fprop_reflect_period_percpu(p, pl);
		num = percpu_counter_read_positive(&pl->events);
		den = percpu_counter_read_positive(&p->events);
	} while (read_seqcount_retry(&p->sequence, seq));

	/*
	 * Make fraction <= 1 and denominator > 0 even in presence of percpu
	 * counter errors
	 */
	if (den <= num) {
		if (num)
			den = num;
		else
			den = 1;
	}
	*denominator = den;
	*numerator = num;
}

/*
 * Like __fprop_inc_percpu() except that event is counted only if the given
 * type has fraction smaller than @max_frac/FPROP_FRAC_BASE
 */
void __fprop_inc_percpu_max(struct fprop_global *p,
			    struct fprop_local_percpu *pl, int max_frac)
{
	if (unlikely(max_frac < FPROP_FRAC_BASE)) {
		unsigned long numerator, denominator;

		fprop_fraction_percpu(p, pl, &numerator, &denominator);
		if (numerator >
		    (((u64)denominator) * max_frac) >> FPROP_FRAC_SHIFT)
			return;
	} else
		fprop_reflect_period_percpu(p, pl);
	__percpu_counter_add(&pl->events, 1, PROP_BATCH);
	percpu_counter_add(&p->events, 1);
}
