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
#ifndef __PLAT_SAMSUNG_CAMPORT_H_
#define __PLAT_SAMSUNG_CAMPORT_H_ __FILE__

enum s5p_camport_id {
	S5P_CAMPORT_A,
	S5P_CAMPORT_B,
};

/*
 * The helper functions to configure GPIO for the camera parallel bus.
 * The camera port can be multiplexed with any FIMC entity, even multiple
 * FIMC entities are allowed to be attached to a single port simultaneously.
 * These functions are to be used in the board setup code.
 */
int s5pv210_fimc_setup_gpio(enum s5p_camport_id id);
int exynos4_fimc_setup_gpio(enum s5p_camport_id id);

#endif /* __PLAT_SAMSUNG_CAMPORT_H */
