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
#ifndef _BEEP_SIGNALFD_H
#define _BEEP_SIGNALFD_H

#include <uapi/beep/signalfd.h>


#ifdef CONFIG_SIGNALFD

/*
 * Deliver the signal to listening signalfd.
 */
static inline void signalfd_notify(struct task_struct *tsk, int sig)
{
	if (unlikely(waitqueue_active(&tsk->sighand->signalfd_wqh)))
		wake_up(&tsk->sighand->signalfd_wqh);
}

extern void signalfd_cleanup(struct sighand_struct *sighand);

#else /* CONFIG_SIGNALFD */

static inline void signalfd_notify(struct task_struct *tsk, int sig) { }

static inline void signalfd_cleanup(struct sighand_struct *sighand) { }

#endif /* CONFIG_SIGNALFD */

#endif /* _BEEP_SIGNALFD_H */
