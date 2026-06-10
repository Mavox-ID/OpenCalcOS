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
#ifndef __PMIC8XXX_PWRKEY_H__
#define __PMIC8XXX_PWRKEY_H__

#define PM8XXX_PWRKEY_DEV_NAME "pm8xxx-pwrkey"

/**
 * struct pm8xxx_pwrkey_platform_data - platform data for pwrkey driver
 * @pull up:  power on register control for pull up/down configuration
 * @kpd_trigger_delay_us: time delay for power key state change interrupt
 *                  trigger.
 * @wakeup: configure power key as wakeup source
 */
struct pm8xxx_pwrkey_platform_data  {
	bool pull_up;
	u32  kpd_trigger_delay_us;
	u32  wakeup;
};

#endif /* __PMIC8XXX_PWRKEY_H__ */
