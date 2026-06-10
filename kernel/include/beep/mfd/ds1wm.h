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
struct ds1wm_driver_data {
	int active_high;
	int clock_rate;
	/* in milliseconds, the amount of time to */
	/* sleep following a reset pulse. Zero    */
	/* should work if your bus devices recover*/
	/* time respects the 1-wire spec since the*/
	/* ds1wm implements the precise timings of*/
	/* a reset pulse/presence detect sequence.*/
	unsigned int reset_recover_delay;
};
