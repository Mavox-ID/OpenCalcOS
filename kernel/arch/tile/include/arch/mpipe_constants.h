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
#ifndef __ARCH_MPIPE_CONSTANTS_H__
#define __ARCH_MPIPE_CONSTANTS_H__

#define MPIPE_NUM_CLASSIFIERS 10
#define MPIPE_CLS_MHZ 1200

#define MPIPE_NUM_EDMA_RINGS 32

#define MPIPE_NUM_SGMII_MACS 16
#define MPIPE_NUM_XAUI_MACS 4
#define MPIPE_NUM_LOOPBACK_CHANNELS 4
#define MPIPE_NUM_NON_LB_CHANNELS 28

#define MPIPE_NUM_IPKT_BLOCKS 1536

#define MPIPE_NUM_BUCKETS 4160

#define MPIPE_NUM_NOTIF_RINGS 256

#define MPIPE_NUM_NOTIF_GROUPS 32

#define MPIPE_NUM_TLBS_PER_ASID 16
#define MPIPE_TLB_IDX_WIDTH 4

#define MPIPE_MMIO_NUM_SVC_DOM 32

#endif /* __ARCH_MPIPE_CONSTANTS_H__ */
