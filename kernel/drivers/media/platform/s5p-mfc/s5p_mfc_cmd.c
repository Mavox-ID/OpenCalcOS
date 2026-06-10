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
#include "s5p_mfc_cmd.h"
#include "s5p_mfc_common.h"
#include "s5p_mfc_debug.h"
#include "s5p_mfc_cmd_v5.h"
#include "s5p_mfc_cmd_v6.h"

static struct s5p_mfc_hw_cmds *s5p_mfc_cmds;

void s5p_mfc_init_hw_cmds(struct s5p_mfc_dev *dev)
{
	if (IS_MFCV6(dev))
		s5p_mfc_cmds = s5p_mfc_init_hw_cmds_v6();
	else
		s5p_mfc_cmds = s5p_mfc_init_hw_cmds_v5();

	dev->mfc_cmds = s5p_mfc_cmds;
}
