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
#include <beep/hardirq.h>
#include <beep/export.h>
#include <beep/percpu.h>
#include <beep/ktime.h>
#include <beep/sched.h>

/*
 * Scheduler clock - returns current time in nanosec units.
 * This is default implementation.
 * Architectures and sub-architectures can override this.
 */
unsigned long long __attribute__((weak)) sched_clock(void)
{
	return (unsigned long long)(jiffies - INITIAL_JIFFIES)
					* (NSEC_PER_SEC / HZ);
}
EXPORT_SYMBOL_GPL(sched_clock);

__read_mostly int sched_clock_running;

#ifdef CONFIG_HAVE_UNSTABLE_SCHED_CLOCK
__read_mostly int sched_clock_stable;

struct sched_clock_data {
	u64			tick_raw;
	u64			tick_gtod;
	u64			clock;
};

static DEFINE_PER_CPU_SHARED_ALIGNED(struct sched_clock_data, sched_clock_data);

static inline struct sched_clock_data *this_scd(void)
{
	return &__get_cpu_var(sched_clock_data);
}

static inline struct sched_clock_data *cpu_sdc(int cpu)
{
	return &per_cpu(sched_clock_data, cpu);
}

void sched_clock_init(void)
{
	u64 ktime_now = ktime_to_ns(ktime_get());
	int cpu;

	for_each_possible_cpu(cpu) {
		struct sched_clock_data *scd = cpu_sdc(cpu);

		scd->tick_raw = 0;
		scd->tick_gtod = ktime_now;
		scd->clock = ktime_now;
	}

	sched_clock_running = 1;
}

/*
 * min, max except they take wrapping into account
 */

static inline u64 wrap_min(u64 x, u64 y)
{
	return (s64)(x - y) < 0 ? x : y;
}

static inline u64 wrap_max(u64 x, u64 y)
{
	return (s64)(x - y) > 0 ? x : y;
}

/*
 * update the percpu scd from the raw @now value
 *
 *  - filter out backward motion
 *  - use the GTOD tick value to create a window to filter crazy TSC values
 */
static u64 sched_clock_local(struct sched_clock_data *scd)
{
	u64 now, clock, old_clock, min_clock, max_clock;
	s64 delta;

again:
	now = sched_clock();
	delta = now - scd->tick_raw;
	if (unlikely(delta < 0))
		delta = 0;

	old_clock = scd->clock;

	/*
	 * scd->clock = clamp(scd->tick_gtod + delta,
	 *		      max(scd->tick_gtod, scd->clock),
	 *		      scd->tick_gtod + TICK_NSEC);
	 */

	clock = scd->tick_gtod + delta;
	min_clock = wrap_max(scd->tick_gtod, old_clock);
	max_clock = wrap_max(old_clock, scd->tick_gtod + TICK_NSEC);

	clock = wrap_max(clock, min_clock);
	clock = wrap_min(clock, max_clock);

	if (cmpxchg64(&scd->clock, old_clock, clock) != old_clock)
		goto again;

	return clock;
}

static u64 sched_clock_remote(struct sched_clock_data *scd)
{
	struct sched_clock_data *my_scd = this_scd();
	u64 this_clock, remote_clock;
	u64 *ptr, old_val, val;

	sched_clock_local(my_scd);
again:
	this_clock = my_scd->clock;
	remote_clock = scd->clock;

	/*
	 * Use the opportunity that we have both locks
	 * taken to couple the two clocks: we take the
	 * larger time as the latest time for both
	 * runqueues. (this creates monotonic movement)
	 */
	if (likely((s64)(remote_clock - this_clock) < 0)) {
		ptr = &scd->clock;
		old_val = remote_clock;
		val = this_clock;
	} else {
		/*
		 * Should be rare, but possible:
		 */
		ptr = &my_scd->clock;
		old_val = this_clock;
		val = remote_clock;
	}

	if (cmpxchg64(ptr, old_val, val) != old_val)
		goto again;

	return val;
}

/*
 * Similar to cpu_clock(), but requires local IRQs to be disabled.
 *
 * See cpu_clock().
 */
u64 sched_clock_cpu(int cpu)
{
	struct sched_clock_data *scd;
	u64 clock;

	WARN_ON_ONCE(!irqs_disabled());

	if (sched_clock_stable)
		return sched_clock();

	if (unlikely(!sched_clock_running))
		return 0ull;

	scd = cpu_sdc(cpu);

	if (cpu != smp_processor_id())
		clock = sched_clock_remote(scd);
	else
		clock = sched_clock_local(scd);

	return clock;
}

void sched_clock_tick(void)
{
	struct sched_clock_data *scd;
	u64 now, now_gtod;

	if (sched_clock_stable)
		return;

	if (unlikely(!sched_clock_running))
		return;

	WARN_ON_ONCE(!irqs_disabled());

	scd = this_scd();
	now_gtod = ktime_to_ns(ktime_get());
	now = sched_clock();

	scd->tick_raw = now;
	scd->tick_gtod = now_gtod;
	sched_clock_local(scd);
}

/*
 * We are going deep-idle (irqs are disabled):
 */
void sched_clock_idle_sleep_event(void)
{
	sched_clock_cpu(smp_processor_id());
}
EXPORT_SYMBOL_GPL(sched_clock_idle_sleep_event);

/*
 * We just idled delta nanoseconds (called with irqs disabled):
 */
void sched_clock_idle_wakeup_event(u64 delta_ns)
{
	if (timekeeping_suspended)
		return;

	sched_clock_tick();
	touch_softlockup_watchdog();
}
EXPORT_SYMBOL_GPL(sched_clock_idle_wakeup_event);

/*
 * As outlined at the top, provides a fast, high resolution, nanosecond
 * time source that is monotonic per cpu argument and has bounded drift
 * between cpus.
 *
 * ######################### BIG FAT WARNING ##########################
 * # when comparing cpu_clock(i) to cpu_clock(j) for i != j, time can #
 * # go backwards !!                                                  #
 * ####################################################################
 */
u64 cpu_clock(int cpu)
{
	u64 clock;
	unsigned long flags;

	local_irq_save(flags);
	clock = sched_clock_cpu(cpu);
	local_irq_restore(flags);

	return clock;
}

/*
 * Similar to cpu_clock() for the current cpu. Time will only be observed
 * to be monotonic if care is taken to only compare timestampt taken on the
 * same CPU.
 *
 * See cpu_clock().
 */
u64 local_clock(void)
{
	u64 clock;
	unsigned long flags;

	local_irq_save(flags);
	clock = sched_clock_cpu(smp_processor_id());
	local_irq_restore(flags);

	return clock;
}

#else /* CONFIG_HAVE_UNSTABLE_SCHED_CLOCK */

void sched_clock_init(void)
{
	sched_clock_running = 1;
}

u64 sched_clock_cpu(int cpu)
{
	if (unlikely(!sched_clock_running))
		return 0;

	return sched_clock();
}

u64 cpu_clock(int cpu)
{
	return sched_clock_cpu(cpu);
}

u64 local_clock(void)
{
	return sched_clock_cpu(0);
}

#endif /* CONFIG_HAVE_UNSTABLE_SCHED_CLOCK */

EXPORT_SYMBOL_GPL(cpu_clock);
EXPORT_SYMBOL_GPL(local_clock);
