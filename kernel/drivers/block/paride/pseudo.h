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
/* Changes:

	1.01	1998.05.03	Switched from cli()/sti() to spinlocks
	1.02    1998.12.14      Added support for nice > 1
*/
	
#define PS_VERSION	"1.02"

#include <beep/sched.h>
#include <beep/workqueue.h>

static void ps_tq_int(struct work_struct *work);

static void (* ps_continuation)(void);
static int (* ps_ready)(void);
static unsigned long ps_timeout;
static int ps_tq_active = 0;
static int ps_nice = 0;

static DEFINE_SPINLOCK(ps_spinlock __attribute__((unused)));

static DECLARE_DELAYED_WORK(ps_tq, ps_tq_int);

static void ps_set_intr(void (*continuation)(void), 
			int (*ready)(void),
			int timeout, int nice)
{
	unsigned long	flags;

	spin_lock_irqsave(&ps_spinlock,flags);

	ps_continuation = continuation;
	ps_ready = ready;
	ps_timeout = jiffies + timeout;
	ps_nice = nice;

	if (!ps_tq_active) {
		ps_tq_active = 1;
		if (!ps_nice)
			schedule_delayed_work(&ps_tq, 0);
		else
			schedule_delayed_work(&ps_tq, ps_nice-1);
	}
	spin_unlock_irqrestore(&ps_spinlock,flags);
}

static void ps_tq_int(struct work_struct *work)
{
	void (*con)(void);
	unsigned long flags;

	spin_lock_irqsave(&ps_spinlock,flags);

	con = ps_continuation;
	ps_tq_active = 0;

	if (!con) {
		spin_unlock_irqrestore(&ps_spinlock,flags);
		return;
	}
	if (!ps_ready || ps_ready() || time_after_eq(jiffies, ps_timeout)) {
		ps_continuation = NULL;
		spin_unlock_irqrestore(&ps_spinlock,flags);
		con();
		return;
	}
	ps_tq_active = 1;
	if (!ps_nice)
		schedule_delayed_work(&ps_tq, 0);
	else
		schedule_delayed_work(&ps_tq, ps_nice-1);
	spin_unlock_irqrestore(&ps_spinlock,flags);
}

/* end of pseudo.h */

