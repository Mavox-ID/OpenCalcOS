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
#ifndef __NLM_HAL_CPUCONTROL_H__
#define __NLM_HAL_CPUCONTROL_H__

#define CPU_BLOCKID_IFU		0
#define CPU_BLOCKID_ICU		1
#define CPU_BLOCKID_IEU		2
#define CPU_BLOCKID_LSU		3
#define CPU_BLOCKID_MMU		4
#define CPU_BLOCKID_PRF		5
#define CPU_BLOCKID_SCH		7
#define CPU_BLOCKID_SCU		8
#define CPU_BLOCKID_FPU		9
#define CPU_BLOCKID_MAP		10

#define LSU_DEFEATURE		0x304
#define LSU_DEBUG_ADDR		0x305
#define LSU_DEBUG_DATA0		0x306
#define LSU_CERRLOG_REGID	0x309
#define SCHED_DEFEATURE		0x700

/* Offsets of interest from the 'MAP' Block */
#define MAP_THREADMODE			0x00
#define MAP_EXT_EBASE_ENABLE		0x04
#define MAP_CCDI_CONFIG			0x08
#define MAP_THRD0_CCDI_STATUS		0x0c
#define MAP_THRD1_CCDI_STATUS		0x10
#define MAP_THRD2_CCDI_STATUS		0x14
#define MAP_THRD3_CCDI_STATUS		0x18
#define MAP_THRD0_DEBUG_MODE		0x1c
#define MAP_THRD1_DEBUG_MODE		0x20
#define MAP_THRD2_DEBUG_MODE		0x24
#define MAP_THRD3_DEBUG_MODE		0x28
#define MAP_MISC_STATE			0x60
#define MAP_DEBUG_READ_CTL		0x64
#define MAP_DEBUG_READ_REG0		0x68
#define MAP_DEBUG_READ_REG1		0x6c

#define MMU_SETUP		0x400
#define MMU_LFSRSEED		0x401
#define MMU_HPW_NUM_PAGE_LVL	0x410
#define MMU_PGWKR_PGDBASE	0x411
#define MMU_PGWKR_PGDSHFT	0x412
#define MMU_PGWKR_PGDMASK	0x413
#define MMU_PGWKR_PUDSHFT	0x414
#define MMU_PGWKR_PUDMASK	0x415
#define MMU_PGWKR_PMDSHFT	0x416
#define MMU_PGWKR_PMDMASK	0x417
#define MMU_PGWKR_PTESHFT	0x418
#define MMU_PGWKR_PTEMASK	0x419

#endif /* __NLM_CPUCONTROL_H__ */
