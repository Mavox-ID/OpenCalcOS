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
#ifndef	_SCSI_SCSI_IU_H
#define _SCSI_SCSI_IU_H 1

struct scsi_status_iu_header
{
	u_int8_t reserved[2];
	u_int8_t flags;
#define	SIU_SNSVALID 0x2
#define	SIU_RSPVALID 0x1
	u_int8_t status;
	u_int8_t sense_length[4];
	u_int8_t pkt_failures_length[4];
	u_int8_t pkt_failures[1];
};

#define SIU_PKTFAIL_OFFSET(siu) 12
#define SIU_PKTFAIL_CODE(siu) (scsi_4btoul((siu)->pkt_failures) & 0xFF)
#define		SIU_PFC_NONE			0
#define		SIU_PFC_CIU_FIELDS_INVALID	2
#define		SIU_PFC_TMF_NOT_SUPPORTED	4
#define		SIU_PFC_TMF_FAILED		5
#define		SIU_PFC_INVALID_TYPE_CODE	6
#define		SIU_PFC_ILLEGAL_REQUEST		7
#define SIU_SENSE_OFFSET(siu)				\
    (12 + (((siu)->flags & SIU_RSPVALID)		\
	? scsi_4btoul((siu)->pkt_failures_length)	\
	: 0))

#define	SIU_TASKMGMT_NONE		0x00
#define	SIU_TASKMGMT_ABORT_TASK		0x01
#define	SIU_TASKMGMT_ABORT_TASK_SET	0x02
#define	SIU_TASKMGMT_CLEAR_TASK_SET	0x04
#define	SIU_TASKMGMT_LUN_RESET		0x08
#define	SIU_TASKMGMT_TARGET_RESET	0x20
#define	SIU_TASKMGMT_CLEAR_ACA		0x40
#endif /*_SCSI_SCSI_IU_H*/
