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
#ifndef __BEEP_USB_TMC_H
#define __BEEP_USB_TMC_H

/* USB TMC status values */
#define USBTMC_STATUS_SUCCESS				0x01
#define USBTMC_STATUS_PENDING				0x02
#define USBTMC_STATUS_FAILED				0x80
#define USBTMC_STATUS_TRANSFER_NOT_IN_PROGRESS		0x81
#define USBTMC_STATUS_SPLIT_NOT_IN_PROGRESS		0x82
#define USBTMC_STATUS_SPLIT_IN_PROGRESS			0x83

/* USB TMC requests values */
#define USBTMC_REQUEST_INITIATE_ABORT_BULK_OUT		1
#define USBTMC_REQUEST_CHECK_ABORT_BULK_OUT_STATUS	2
#define USBTMC_REQUEST_INITIATE_ABORT_BULK_IN		3
#define USBTMC_REQUEST_CHECK_ABORT_BULK_IN_STATUS	4
#define USBTMC_REQUEST_INITIATE_CLEAR			5
#define USBTMC_REQUEST_CHECK_CLEAR_STATUS		6
#define USBTMC_REQUEST_GET_CAPABILITIES			7
#define USBTMC_REQUEST_INDICATOR_PULSE			64

/* Request values for USBTMC driver's ioctl entry point */
#define USBTMC_IOC_NR			91
#define USBTMC_IOCTL_INDICATOR_PULSE	_IO(USBTMC_IOC_NR, 1)
#define USBTMC_IOCTL_CLEAR		_IO(USBTMC_IOC_NR, 2)
#define USBTMC_IOCTL_ABORT_BULK_OUT	_IO(USBTMC_IOC_NR, 3)
#define USBTMC_IOCTL_ABORT_BULK_IN	_IO(USBTMC_IOC_NR, 4)
#define USBTMC_IOCTL_CLEAR_OUT_HALT	_IO(USBTMC_IOC_NR, 6)
#define USBTMC_IOCTL_CLEAR_IN_HALT	_IO(USBTMC_IOC_NR, 7)

#endif
