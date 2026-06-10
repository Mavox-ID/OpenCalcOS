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
#ifndef __iwl_power_setting_h__
#define __iwl_power_setting_h__

#include "commands.h"

struct iwl_power_mgr {
	struct iwl_powertable_cmd sleep_cmd;
	struct iwl_powertable_cmd sleep_cmd_next;
	int debug_sleep_level_override;
	bool bus_pm;
};

int iwl_power_set_mode(struct iwl_priv *priv, struct iwl_powertable_cmd *cmd,
		       bool force);
int iwl_power_update_mode(struct iwl_priv *priv, bool force);
void iwl_power_initialize(struct iwl_priv *priv);

extern bool no_sleep_autoadjust;

#endif  /* __iwl_power_setting_h__ */
