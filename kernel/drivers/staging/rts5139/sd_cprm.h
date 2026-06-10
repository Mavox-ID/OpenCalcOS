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
#ifndef __RTS51X_SD_CPRM_H
#define __RTS51X_SD_CPRM_H

#include "rts51x_chip.h"
#include "sd.h"

#ifdef SUPPORT_CPRM
int ext_rts51x_sd_execute_no_data(struct rts51x_chip *chip, unsigned int lun,
			   u8 cmd_idx, u8 standby, u8 acmd, u8 rsp_code,
			   u32 arg);
int ext_rts51x_sd_execute_read_data(struct rts51x_chip *chip, unsigned int lun,
			     u8 cmd_idx, u8 cmd12, u8 standby, u8 acmd,
			     u8 rsp_code, u32 arg, u32 data_len, void *data_buf,
			     unsigned int buf_len, int use_sg);
int ext_rts51x_sd_execute_write_data(struct rts51x_chip *chip, unsigned int lun,
			      u8 cmd_idx, u8 cmd12, u8 standby, u8 acmd,
			      u8 rsp_code, u32 arg, u32 data_len,
			      void *data_buf, unsigned int buf_len, int use_sg);

int rts51x_sd_pass_thru_mode(struct scsi_cmnd *srb, struct rts51x_chip *chip);
int rts51x_sd_execute_no_data(struct scsi_cmnd *srb, struct rts51x_chip *chip);
int rts51x_sd_execute_read_data(struct scsi_cmnd *srb, struct rts51x_chip *chip);
int rts51x_sd_execute_write_data(struct scsi_cmnd *srb, struct rts51x_chip *chip);
int rts51x_sd_get_cmd_rsp(struct scsi_cmnd *srb, struct rts51x_chip *chip);
int rts51x_sd_hw_rst(struct scsi_cmnd *srb, struct rts51x_chip *chip);
#endif

#endif /* __RTS51X_SD_CPRM_H */
