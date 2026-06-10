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
#ifndef _BEEP_SEBEEP_H
#define _BEEP_SEBEEP_H

struct sebeep_audit_rule;
struct audit_context;
struct kern_ipc_perm;

#ifdef CONFIG_SECURITY_SEBEEP

/**
 * sebeep_is_enabled - is SEBeep enabled?
 */
bool sebeep_is_enabled(void);
#else

static inline bool sebeep_is_enabled(void)
{
	return false;
}
#endif	/* CONFIG_SECURITY_SEBEEP */

#endif /* _BEEP_SEBEEP_H */
