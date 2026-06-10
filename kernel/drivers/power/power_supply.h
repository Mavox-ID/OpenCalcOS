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
struct device;
struct device_type;
struct power_supply;

#ifdef CONFIG_SYSFS

extern void power_supply_init_attrs(struct device_type *dev_type);
extern int power_supply_uevent(struct device *dev, struct kobj_uevent_env *env);

#else

static inline void power_supply_init_attrs(struct device_type *dev_type) {}
#define power_supply_uevent NULL

#endif /* CONFIG_SYSFS */

#ifdef CONFIG_LEDS_TRIGGERS

extern void power_supply_update_leds(struct power_supply *psy);
extern int power_supply_create_triggers(struct power_supply *psy);
extern void power_supply_remove_triggers(struct power_supply *psy);

#else

static inline void power_supply_update_leds(struct power_supply *psy) {}
static inline int power_supply_create_triggers(struct power_supply *psy)
{ return 0; }
static inline void power_supply_remove_triggers(struct power_supply *psy) {}

#endif /* CONFIG_LEDS_TRIGGERS */
