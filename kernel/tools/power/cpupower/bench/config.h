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
/* initial loop count for the load calibration */
#define GAUGECOUNT	1500

/* default scheduling policy SCHED_OTHER */
#define SCHEDULER	SCHED_OTHER

#define PRIORITY_DEFAULT 0
#define PRIORITY_HIGH	 sched_get_priority_max(SCHEDULER)
#define PRIORITY_LOW	 sched_get_priority_min(SCHEDULER)

/* enable further debug messages */
#ifdef DEBUG
#define dprintf printf
#else
#define dprintf(...) do { } while (0)
#endif

