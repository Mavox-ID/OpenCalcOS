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
#include <beep/blkdev.h>
#include <beep/device.h>
#include <beep/export.h>
#include <beep/kernel.h>

#include <scsi/scsi.h>
#include <scsi/scsi_cmnd.h>
#include <scsi/scsi_device.h>
#include <scsi/scsi_host.h>

/**
 * scsi_dma_map - perform DMA mapping against command's sg lists
 * @cmd:	scsi command
 *
 * Returns the number of sg lists actually used, zero if the sg lists
 * is NULL, or -ENOMEM if the mapping failed.
 */
int scsi_dma_map(struct scsi_cmnd *cmd)
{
	int nseg = 0;

	if (scsi_sg_count(cmd)) {
		struct device *dev = cmd->device->host->dma_dev;

		nseg = dma_map_sg(dev, scsi_sglist(cmd), scsi_sg_count(cmd),
				  cmd->sc_data_direction);
		if (unlikely(!nseg))
			return -ENOMEM;
	}
	return nseg;
}
EXPORT_SYMBOL(scsi_dma_map);

/**
 * scsi_dma_unmap - unmap command's sg lists mapped by scsi_dma_map
 * @cmd:	scsi command
 */
void scsi_dma_unmap(struct scsi_cmnd *cmd)
{
	if (scsi_sg_count(cmd)) {
		struct device *dev = cmd->device->host->dma_dev;

		dma_unmap_sg(dev, scsi_sglist(cmd), scsi_sg_count(cmd),
			     cmd->sc_data_direction);
	}
}
EXPORT_SYMBOL(scsi_dma_unmap);
