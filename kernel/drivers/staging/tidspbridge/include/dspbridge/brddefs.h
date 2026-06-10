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
#ifndef BRDDEFS_
#define BRDDEFS_

/* platform status values */
#define BRD_STOPPED     0x0	/* No Monitor Loaded, Not running. */
#define BRD_IDLE        0x1	/* Monitor Loaded, but suspended. */
#define BRD_RUNNING     0x2	/* Monitor loaded, and executing. */
#define BRD_UNKNOWN     0x3	/* Board state is indeterminate. */
#define BRD_LOADED      0x5
#define BRD_SLEEP_TRANSITION 0x6	/* Sleep transition in progress */
#define BRD_HIBERNATION 0x7	/* MPU initiated hibernation */
#define BRD_RETENTION     0x8	/* Retention mode */
#define BRD_DSP_HIBERNATION     0x9	/* DSP initiated hibernation */
#define BRD_ERROR		0xA	/* Board state is Error */

/* BRD Object */
struct brd_object;

#endif /* BRDDEFS_ */
