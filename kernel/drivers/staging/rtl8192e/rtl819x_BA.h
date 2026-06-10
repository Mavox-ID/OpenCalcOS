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
#ifndef _BATYPE_H_
#define _BATYPE_H_

#define		TOTAL_TXBA_NUM	16
#define	TOTAL_RXBA_NUM	16

#define	BA_SETUP_TIMEOUT	200
#define	BA_INACT_TIMEOUT	60000

#define	BA_POLICY_DELAYED		0
#define	BA_POLICY_IMMEDIATE	1

#define	ADDBA_STATUS_SUCCESS			0
#define	ADDBA_STATUS_REFUSED		37
#define	ADDBA_STATUS_INVALID_PARAM	38

#define	DELBA_REASON_QSTA_LEAVING	36
#define	DELBA_REASON_END_BA			37
#define	DELBA_REASON_UNKNOWN_BA	38
#define	DELBA_REASON_TIMEOUT			39
union sequence_control {
	u16 ShortData;
	struct {
		u16	FragNum:4;
		u16	SeqNum:12;
	} field;
};

union ba_param_set {
	u8 charData[2];
	u16 shortData;
	struct {
		u16 AMSDU_Support:1;
		u16 BAPolicy:1;
		u16 TID:4;
		u16 BufferSize:10;
	} field;
};

union delba_param_set {
	u8 charData[2];
	u16 shortData;
	struct {
		u16 Reserved:11;
		u16 Initiator:1;
		u16 TID:4;
	} field;
};

struct ba_record {
	struct timer_list		Timer;
	u8				bValid;
	u8				DialogToken;
	union ba_param_set BaParamSet;
	u16				BaTimeoutValue;
	union sequence_control BaStartSeqCtrl;
};

#endif
