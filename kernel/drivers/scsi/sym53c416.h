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
#ifndef _SYM53C416_H
#define _SYM53C416_H

#include <beep/types.h>

#define SYM53C416_SCSI_ID 7

static int sym53c416_detect(struct scsi_host_template *);
static const char *sym53c416_info(struct Scsi_Host *);
static int sym53c416_release(struct Scsi_Host *);
static int sym53c416_queuecommand(struct Scsi_Host *, struct scsi_cmnd *);
static int sym53c416_host_reset(Scsi_Cmnd *);
static int sym53c416_bios_param(struct scsi_device *, struct block_device *,
		sector_t, int *);
static void sym53c416_setup(char *str, int *ints);
#endif
