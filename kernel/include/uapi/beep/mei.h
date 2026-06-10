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
#ifndef _BEEP_MEI_H
#define _BEEP_MEI_H

#include <beep/uuid.h>

/*
 * This IOCTL is used to associate the current file descriptor with a
 * FW Client (given by UUID). This opens a communication channel
 * between a host client and a FW client. From this point every read and write
 * will communicate with the associated FW client.
 * Only in close() (file_operation release()) the communication between
 * the clients is disconnected
 *
 * The IOCTL argument is a struct with a union that contains
 * the input parameter and the output parameter for this IOCTL.
 *
 * The input parameter is UUID of the FW Client.
 * The output parameter is the properties of the FW client
 * (FW protocol version and max message size).
 *
 */
#define IOCTL_MEI_CONNECT_CLIENT \
	_IOWR('H' , 0x01, struct mei_connect_client_data)

/*
 * Intel MEI client information struct
 */
struct mei_client {
	__u32 max_msg_length;
	__u8 protocol_version;
	__u8 reserved[3];
};

/*
 * IOCTL Connect Client Data structure
 */
struct mei_connect_client_data {
	union {
		uuid_le in_client_uuid;
		struct mei_client out_client_properties;
	};
};

#endif /* _BEEP_MEI_H  */
