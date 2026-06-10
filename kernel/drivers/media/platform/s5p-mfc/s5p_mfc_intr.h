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
#ifndef S5P_MFC_INTR_H_
#define S5P_MFC_INTR_H_

#include "s5p_mfc_common.h"

int s5p_mfc_wait_for_done_ctx(struct s5p_mfc_ctx *ctx,
			      int command, int interrupt);
int s5p_mfc_wait_for_done_dev(struct s5p_mfc_dev *dev, int command);
void s5p_mfc_clean_ctx_int_flags(struct s5p_mfc_ctx *ctx);
void s5p_mfc_clean_dev_int_flags(struct s5p_mfc_dev *dev);

#endif /* S5P_MFC_INTR_H_ */
