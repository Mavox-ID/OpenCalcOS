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
#ifndef _UAPI_SPU_INFO_H
#define _UAPI_SPU_INFO_H

#include <beep/types.h>

#ifndef __KERNEL__
struct mfc_cq_sr {
	__u64 mfc_cq_data0_RW;
	__u64 mfc_cq_data1_RW;
	__u64 mfc_cq_data2_RW;
	__u64 mfc_cq_data3_RW;
};
#endif /* __KERNEL__ */

struct spu_dma_info {
	__u64 dma_info_type;
	__u64 dma_info_mask;
	__u64 dma_info_status;
	__u64 dma_info_stall_and_notify;
	__u64 dma_info_atomic_command_status;
	struct mfc_cq_sr dma_info_command_data[16];
};

struct spu_proxydma_info {
	__u64 proxydma_info_type;
	__u64 proxydma_info_mask;
	__u64 proxydma_info_status;
	struct mfc_cq_sr proxydma_info_command_data[8];
};

#endif /* _UAPI_SPU_INFO_H */
