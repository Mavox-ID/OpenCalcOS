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
#ifndef _BEEP_I2C_PCA954X_H
#define _BEEP_I2C_PCA954X_H

/* Platform data for the PCA954x I2C multiplexers */

/* Per channel initialisation data:
 * @adap_id: bus number for the adapter. 0 = don't care
 * @deselect_on_exit: set this entry to 1, if your H/W needs deselection
 *                    of this channel after transaction.
 *
 */
struct pca954x_platform_mode {
	int		adap_id;
	unsigned int	deselect_on_exit:1;
	unsigned int	class;
};

/* Per mux/switch data, used with i2c_register_board_info */
struct pca954x_platform_data {
	struct pca954x_platform_mode *modes;
	int num_modes;
};

#endif /* _BEEP_I2C_PCA954X_H */
