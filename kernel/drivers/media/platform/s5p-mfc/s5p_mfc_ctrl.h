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
#ifndef S5P_MFC_CTRL_H
#define S5P_MFC_CTRL_H

#include "s5p_mfc_common.h"

int s5p_mfc_release_firmware(struct s5p_mfc_dev *dev);
int s5p_mfc_alloc_and_load_firmware(struct s5p_mfc_dev *dev);
int s5p_mfc_reload_firmware(struct s5p_mfc_dev *dev);

int s5p_mfc_init_hw(struct s5p_mfc_dev *dev);
void s5p_mfc_deinit_hw(struct s5p_mfc_dev *dev);

int s5p_mfc_sleep(struct s5p_mfc_dev *dev);
int s5p_mfc_wakeup(struct s5p_mfc_dev *dev);

int s5p_mfc_reset(struct s5p_mfc_dev *dev);

#endif /* S5P_MFC_CTRL_H */
