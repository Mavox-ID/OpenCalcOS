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
#ifndef _BEEP_MWAVEPUB_H
#define _BEEP_MWAVEPUB_H

#include <beep/miscdevice.h>


typedef struct _MW_ABILITIES {
	unsigned long instr_per_sec;
	unsigned long data_size;
	unsigned long inst_size;
	unsigned long bus_dma_bw;
	unsigned short uart_enable;
	short component_count;
	unsigned long component_list[7];
	char mwave_os_name[16];
	char bios_task_name[16];
} MW_ABILITIES, *pMW_ABILITIES;


typedef struct _MW_READWRITE {
	unsigned short usDspAddress;	/* The dsp address */
	unsigned long ulDataLength;	/* The size in bytes of the data or user buffer */
	void __user *pBuf;		/* Input:variable sized buffer */
} MW_READWRITE, *pMW_READWRITE;

#define IOCTL_MW_RESET           _IO(MWAVE_MINOR,1)
#define IOCTL_MW_RUN             _IO(MWAVE_MINOR,2)
#define IOCTL_MW_DSP_ABILITIES   _IOR(MWAVE_MINOR,3,MW_ABILITIES)
#define IOCTL_MW_READ_DATA       _IOR(MWAVE_MINOR,4,MW_READWRITE)
#define IOCTL_MW_READCLEAR_DATA  _IOR(MWAVE_MINOR,5,MW_READWRITE)
#define IOCTL_MW_READ_INST       _IOR(MWAVE_MINOR,6,MW_READWRITE)
#define IOCTL_MW_WRITE_DATA      _IOW(MWAVE_MINOR,7,MW_READWRITE)
#define IOCTL_MW_WRITE_INST      _IOW(MWAVE_MINOR,8,MW_READWRITE)
#define IOCTL_MW_REGISTER_IPC    _IOW(MWAVE_MINOR,9,int)
#define IOCTL_MW_UNREGISTER_IPC  _IOW(MWAVE_MINOR,10,int)
#define IOCTL_MW_GET_IPC         _IOW(MWAVE_MINOR,11,int)
#define IOCTL_MW_TRACE           _IOR(MWAVE_MINOR,12,MW_READWRITE)


#endif
