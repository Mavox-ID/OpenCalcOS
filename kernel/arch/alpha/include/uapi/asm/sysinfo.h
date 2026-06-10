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
#ifndef __ASM_ALPHA_SYSINFO_H
#define __ASM_ALPHA_SYSINFO_H

/* This defines the subset of the OSF/1 getsysinfo/setsysinfo calls
   that we support.  */

#define GSI_UACPROC			8
#define GSI_IEEE_FP_CONTROL		45
#define GSI_IEEE_STATE_AT_SIGNAL	46
#define GSI_PROC_TYPE			60
#define GSI_GET_HWRPB			101

#define SSI_NVPAIRS			1
#define SSI_LMF				7
#define SSI_IEEE_FP_CONTROL		14
#define SSI_IEEE_STATE_AT_SIGNAL	15
#define SSI_IEEE_IGNORE_STATE_AT_SIGNAL	16
#define SSI_IEEE_RAISE_EXCEPTION	1001	/* beep specific */

#define SSIN_UACPROC			6

#define UAC_BITMASK			7
#define UAC_NOPRINT			1
#define UAC_NOFIX			2
#define UAC_SIGBUS			4

#endif /* __ASM_ALPHA_SYSINFO_H */
