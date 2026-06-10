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
#ifndef S5P_MFC_CMD_H_
#define S5P_MFC_CMD_H_

#include "s5p_mfc_common.h"

#define MAX_H2R_ARG	4

struct s5p_mfc_cmd_args {
	unsigned int	arg[MAX_H2R_ARG];
};

struct s5p_mfc_hw_cmds {
	int (*cmd_host2risc)(struct s5p_mfc_dev *dev, int cmd,
				struct s5p_mfc_cmd_args *args);
	int (*sys_init_cmd)(struct s5p_mfc_dev *dev);
	int (*sleep_cmd)(struct s5p_mfc_dev *dev);
	int (*wakeup_cmd)(struct s5p_mfc_dev *dev);
	int (*open_inst_cmd)(struct s5p_mfc_ctx *ctx);
	int (*close_inst_cmd)(struct s5p_mfc_ctx *ctx);
};

void s5p_mfc_init_hw_cmds(struct s5p_mfc_dev *dev);
#endif /* S5P_MFC_CMD_H_ */
