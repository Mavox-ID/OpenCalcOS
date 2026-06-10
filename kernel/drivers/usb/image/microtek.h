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
typedef void (*mts_scsi_cmnd_callback)(struct scsi_cmnd *);


struct mts_transfer_context
{
	struct mts_desc* instance;
	mts_scsi_cmnd_callback final_callback;
	struct scsi_cmnd *srb;
	
	void* data;
	unsigned data_length;
	int data_pipe;
	int fragment;

	u8 *scsi_status; /* status returned from ep_response after command completion */
};


struct mts_desc {
	struct mts_desc *next;
	struct mts_desc *prev;

	struct usb_device *usb_dev;
	struct usb_interface *usb_intf;

	/* Endpoint addresses */
	u8 ep_out;
	u8 ep_response;
	u8 ep_image;

	struct Scsi_Host * host;

	struct urb *urb;
	struct mts_transfer_context context;
};


#define MTS_EP_OUT	0x1
#define MTS_EP_RESPONSE	0x2
#define MTS_EP_IMAGE	0x3
#define MTS_EP_TOTAL	0x3

#define MTS_SCSI_ERR_MASK ~0x3fu

