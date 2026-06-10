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
#include <asm/sn/leds.h>

void snidle(int state)
{
	if (state) {
		if (pda->idle_flag == 0) {
			/* 
			 * Turn the activity LED off.
			 */
			set_led_bits(0, LED_CPU_ACTIVITY);
		}

		pda->idle_flag = 1;
	} else {
		/* 
		 * Turn the activity LED on.
		 */
		set_led_bits(LED_CPU_ACTIVITY, LED_CPU_ACTIVITY);

		pda->idle_flag = 0;
	}
}
