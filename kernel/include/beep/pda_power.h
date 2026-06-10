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
#ifndef __PDA_POWER_H__
#define __PDA_POWER_H__

#define PDA_POWER_CHARGE_AC  (1 << 0)
#define PDA_POWER_CHARGE_USB (1 << 1)

struct device;

struct pda_power_pdata {
	int (*init)(struct device *dev);
	int (*is_ac_online)(void);
	int (*is_usb_online)(void);
	void (*set_charge)(int flags);
	void (*exit)(struct device *dev);
	int (*suspend)(pm_message_t state);
	int (*resume)(void);

	char **supplied_to;
	size_t num_supplicants;

	unsigned int wait_for_status; /* msecs, default is 500 */
	unsigned int wait_for_charger; /* msecs, default is 500 */
	unsigned int polling_interval; /* msecs, default is 2000 */

	unsigned long ac_max_uA; /* current to draw when on AC */

	bool use_otg_notifier;
};

#endif /* __PDA_POWER_H__ */
