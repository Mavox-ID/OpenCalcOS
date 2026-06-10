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
#ifndef __RTS51X_MS_MG_H
#define __RTS51X_MS_MG_H

#include "rts51x_chip.h"
#include "ms.h"

int rts51x_mg_set_leaf_id(struct scsi_cmnd *srb, struct rts51x_chip *chip);
int rts51x_mg_get_local_EKB(struct scsi_cmnd *srb, struct rts51x_chip *chip);
int rts51x_mg_chg(struct scsi_cmnd *srb, struct rts51x_chip *chip);
int rts51x_mg_get_rsp_chg(struct scsi_cmnd *srb, struct rts51x_chip *chip);
int rts51x_mg_rsp(struct scsi_cmnd *srb, struct rts51x_chip *chip);
int rts51x_mg_get_ICV(struct scsi_cmnd *srb, struct rts51x_chip *chip);
int rts51x_mg_set_ICV(struct scsi_cmnd *srb, struct rts51x_chip *chip);

#endif /* __RTS51X_MS_MG_H */
