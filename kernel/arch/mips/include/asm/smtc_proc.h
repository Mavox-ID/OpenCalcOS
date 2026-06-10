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
#ifndef __ASM_SMTC_PROC_H
#define __ASM_SMTC_PROC_H

/*
 * per-"CPU" statistics
 */

struct smtc_cpu_proc {
	unsigned long timerints;
	unsigned long selfipis;
};

extern struct smtc_cpu_proc smtc_cpu_stats[NR_CPUS];

/* Count of number of recoveries of "stolen" FPU access rights on 34K */

extern atomic_t smtc_fpu_recoveries;

#endif /* __ASM_SMTC_PROC_H */
