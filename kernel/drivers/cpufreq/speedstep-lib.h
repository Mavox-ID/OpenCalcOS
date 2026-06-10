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
/* processors */
enum speedstep_processor {
	SPEEDSTEP_CPU_PIII_C_EARLY = 0x00000001,  /* Coppermine core */
	SPEEDSTEP_CPU_PIII_C	   = 0x00000002,  /* Coppermine core */
	SPEEDSTEP_CPU_PIII_T	   = 0x00000003,  /* Tualatin core */
	SPEEDSTEP_CPU_P4M	   = 0x00000004,  /* P4-M  */
/* the following processors are not speedstep-capable and are not auto-detected
 * in speedstep_detect_processor(). However, their speed can be detected using
 * the speedstep_get_frequency() call. */
	SPEEDSTEP_CPU_PM	   = 0xFFFFFF03,  /* Pentium M  */
	SPEEDSTEP_CPU_P4D	   = 0xFFFFFF04,  /* desktop P4  */
	SPEEDSTEP_CPU_PCORE	   = 0xFFFFFF05,  /* Core */
};

/* speedstep states -- only two of them */

#define SPEEDSTEP_HIGH	0x00000000
#define SPEEDSTEP_LOW	0x00000001


/* detect a speedstep-capable processor */
extern enum speedstep_processor speedstep_detect_processor(void);

/* detect the current speed (in khz) of the processor */
extern unsigned int speedstep_get_frequency(enum speedstep_processor processor);


/* detect the low and high speeds of the processor. The callback
 * set_state"'s first argument is either SPEEDSTEP_HIGH or
 * SPEEDSTEP_LOW; the second argument is zero so that no
 * cpufreq_notify_transition calls are initiated.
 */
extern unsigned int speedstep_get_freqs(enum speedstep_processor processor,
	unsigned int *low_speed,
	unsigned int *high_speed,
	unsigned int *transition_latency,
	void (*set_state) (unsigned int state));
