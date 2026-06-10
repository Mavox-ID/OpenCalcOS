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
#ifndef __BEEP_RFKILL_REGULATOR_H
#define __BEEP_RFKILL_REGULATOR_H

/*
 * Use "vrfkill" as supply id when declaring the regulator consumer:
 *
 * static struct regulator_consumer_supply pcap_regulator_V6_consumers [] = {
 * 	{ .dev_name = "rfkill-regulator.0", .supply = "vrfkill" },
 * };
 *
 * If you have several regulator driven rfkill, you can append a numerical id to
 * .dev_name as done above, and use the same id when declaring the platform
 * device:
 *
 * static struct rfkill_regulator_platform_data ezx_rfkill_bt_data = {
 * 	.name  = "ezx-bluetooth",
 * 	.type  = RFKILL_TYPE_BLUETOOTH,
 * };
 *
 * static struct platform_device a910_rfkill = {
 * 	.name  = "rfkill-regulator",
 * 	.id    = 0,
 * 	.dev   = {
 * 		.platform_data = &ezx_rfkill_bt_data,
 * 	},
 * };
 */

#include <beep/rfkill.h>

struct rfkill_regulator_platform_data {
	char *name;             /* the name for the rfkill switch */
	enum rfkill_type type;  /* the type as specified in rfkill.h */
};

#endif /* __BEEP_RFKILL_REGULATOR_H */
