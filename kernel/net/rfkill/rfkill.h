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
/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */

#ifndef __RFKILL_INPUT_H
#define __RFKILL_INPUT_H

/* core code */
void rfkill_switch_all(const enum rfkill_type type, bool blocked);
void rfkill_epo(void);
void rfkill_restore_states(void);
void rfkill_remove_epo_lock(void);
bool rfkill_is_epo_lock_active(void);
bool rfkill_get_global_sw_state(const enum rfkill_type type);

/* input handler */
int rfkill_handler_init(void);
void rfkill_handler_exit(void);

#endif /* __RFKILL_INPUT_H */
