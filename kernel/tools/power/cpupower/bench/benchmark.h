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
/* load loop, this schould take about 1 to 2ms to complete */
#define ROUNDS(x) {unsigned int rcnt;			       \
		for (rcnt = 0; rcnt < x*1000; rcnt++) { \
			(void)(((int)(pow(rcnt, rcnt) * \
				      sqrt(rcnt*7230970)) ^ 7230716) ^ \
				      (int)atan2(rcnt, rcnt));	       \
		} }							\


void start_benchmark(struct config *config);
