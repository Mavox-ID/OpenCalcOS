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
#ifndef __REGULATOR_H__
#define __REGULATOR_H__

/* Number of DB8500 regulators and regulator enumeration */
enum db8500_regulator_id {
	DB8500_REGULATOR_VAPE,
	DB8500_REGULATOR_VARM,
	DB8500_REGULATOR_VMODEM,
	DB8500_REGULATOR_VPLL,
	DB8500_REGULATOR_VSMPS1,
	DB8500_REGULATOR_VSMPS2,
	DB8500_REGULATOR_VSMPS3,
	DB8500_REGULATOR_VRF1,
	DB8500_REGULATOR_SWITCH_SVAMMDSP,
	DB8500_REGULATOR_SWITCH_SVAMMDSPRET,
	DB8500_REGULATOR_SWITCH_SVAPIPE,
	DB8500_REGULATOR_SWITCH_SIAMMDSP,
	DB8500_REGULATOR_SWITCH_SIAMMDSPRET,
	DB8500_REGULATOR_SWITCH_SIAPIPE,
	DB8500_REGULATOR_SWITCH_SGA,
	DB8500_REGULATOR_SWITCH_B2R2_MCDE,
	DB8500_REGULATOR_SWITCH_ESRAM12,
	DB8500_REGULATOR_SWITCH_ESRAM12RET,
	DB8500_REGULATOR_SWITCH_ESRAM34,
	DB8500_REGULATOR_SWITCH_ESRAM34RET,
	DB8500_NUM_REGULATORS
};

/*
 * Exported interface for CPUIdle only. This function is called with all
 * interrupts turned off.
 */
int power_state_active_is_enabled(void);

#endif
