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
/* $Id: nsp_message.c,v 1.6 2003/07/26 14:21:09 elca Exp $ */

static void nsp_message_in(struct scsi_cmnd *SCpnt)
{
	unsigned int  base = SCpnt->device->host->io_port;
	nsp_hw_data  *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	unsigned char data_reg, control_reg;
	int           ret, len;

	/*
	 * XXX: NSP QUIRK
	 * NSP invoke interrupts only in the case of scsi phase changes,
	 * therefore we should poll the scsi phase here to catch 
	 * the next "msg in" if exists (no scsi phase changes).
	 */
	ret = 16;
	len = 0;

	nsp_dbg(NSP_DEBUG_MSGINOCCUR, "msgin loop");
	do {
		/* read data */
		data_reg = nsp_index_read(base, SCSIDATAIN);

		/* assert ACK */
		control_reg = nsp_index_read(base, SCSIBUSCTRL);
		control_reg |= SCSI_ACK;
		nsp_index_write(base, SCSIBUSCTRL, control_reg);
		nsp_negate_signal(SCpnt, BUSMON_REQ, "msgin<REQ>");

		data->MsgBuffer[len] = data_reg; len++;

		/* deassert ACK */
		control_reg =  nsp_index_read(base, SCSIBUSCTRL);
		control_reg &= ~SCSI_ACK;
		nsp_index_write(base, SCSIBUSCTRL, control_reg);

		/* catch a next signal */
		ret = nsp_expect_signal(SCpnt, BUSPHASE_MESSAGE_IN, BUSMON_REQ);
	} while (ret > 0 && MSGBUF_SIZE > len);

	data->MsgLen = len;

}

static void nsp_message_out(struct scsi_cmnd *SCpnt)
{
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	int ret = 1;
	int len = data->MsgLen;

	/*
	 * XXX: NSP QUIRK
	 * NSP invoke interrupts only in the case of scsi phase changes,
	 * therefore we should poll the scsi phase here to catch 
	 * the next "msg out" if exists (no scsi phase changes).
	 */

	nsp_dbg(NSP_DEBUG_MSGOUTOCCUR, "msgout loop");
	do {
		if (nsp_xfer(SCpnt, BUSPHASE_MESSAGE_OUT)) {
			nsp_msg(KERN_DEBUG, "msgout: xfer short");
		}

		/* catch a next signal */
		ret = nsp_expect_signal(SCpnt, BUSPHASE_MESSAGE_OUT, BUSMON_REQ);
	} while (ret > 0 && len-- > 0);

}

/* end */
