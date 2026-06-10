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
#ifndef __iwl_calib_h__
#define __iwl_calib_h__

#include "dev.h"
#include "commands.h"

void iwl_chain_noise_calibration(struct iwl_priv *priv);
void iwl_sensitivity_calibration(struct iwl_priv *priv);

void iwl_init_sensitivity(struct iwl_priv *priv);
void iwl_reset_run_time_calib(struct iwl_priv *priv);

#endif /* __iwl_calib_h__ */
