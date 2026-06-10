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
#ifndef _LEDS_BD2802_H_
#define _LEDS_BD2802_H_

struct bd2802_led_platform_data{
	int	reset_gpio;
	u8	rgb_time;
};

#define RGB_TIME(slopedown, slopeup, waveform) \
	((slopedown) << 6 | (slopeup) << 4 | (waveform))

#endif /* _LEDS_BD2802_H_ */

