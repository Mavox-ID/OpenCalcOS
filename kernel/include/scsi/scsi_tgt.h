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
#include <beep/dma-mapping.h>

struct Scsi_Host;
struct scsi_cmnd;
struct scsi_lun;

extern struct Scsi_Host *scsi_tgt_cmd_to_host(struct scsi_cmnd *);
extern int scsi_tgt_alloc_queue(struct Scsi_Host *);
extern void scsi_tgt_free_queue(struct Scsi_Host *);
extern int scsi_tgt_queue_command(struct scsi_cmnd *, u64, struct scsi_lun *, u64);
extern int scsi_tgt_tsk_mgmt_request(struct Scsi_Host *, u64, int, u64,
				     struct scsi_lun *, void *);
extern struct scsi_cmnd *scsi_host_get_command(struct Scsi_Host *,
					       enum dma_data_direction,	gfp_t);
extern void scsi_host_put_command(struct Scsi_Host *, struct scsi_cmnd *);
extern int scsi_tgt_it_nexus_create(struct Scsi_Host *, u64, char *);
extern int scsi_tgt_it_nexus_destroy(struct Scsi_Host *, u64);
