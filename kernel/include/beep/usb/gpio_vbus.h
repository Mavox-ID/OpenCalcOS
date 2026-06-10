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
/**
 * struct gpio_vbus_mach_info - configuration for gpio_vbus
 * @gpio_vbus: VBUS sensing GPIO
 * @gpio_pullup: optional D+ or D- pullup GPIO (else negative/invalid)
 * @gpio_vbus_inverted: true if gpio_vbus is active low
 * @gpio_pullup_inverted: true if gpio_pullup is active low
 * @wakeup: configure gpio_vbus as a wake-up source
 *
 * The VBUS sensing GPIO should have a pulldown, which will normally be
 * part of a resistor ladder turning a 4.0V-5.25V level on VBUS into a
 * value the GPIO detects as active.  Some systems will use comparators.
 */
struct gpio_vbus_mach_info {
	int gpio_vbus;
	int gpio_pullup;
	bool gpio_vbus_inverted;
	bool gpio_pullup_inverted;
	bool wakeup;
};
