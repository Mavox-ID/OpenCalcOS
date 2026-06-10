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
#ifndef __WL1251_IO_H__
#define __WL1251_IO_H__

#include "wl1251.h"

#define HW_ACCESS_MEMORY_MAX_RANGE		0x1FFC0

#define HW_ACCESS_PART0_SIZE_ADDR           0x1FFC0
#define HW_ACCESS_PART0_START_ADDR          0x1FFC4
#define HW_ACCESS_PART1_SIZE_ADDR           0x1FFC8
#define HW_ACCESS_PART1_START_ADDR          0x1FFCC

#define HW_ACCESS_REGISTER_SIZE             4

#define HW_ACCESS_PRAM_MAX_RANGE		0x3c000

static inline u32 wl1251_read32(struct wl1251 *wl, int addr)
{
	wl->if_ops->read(wl, addr, &wl->buffer_32, sizeof(wl->buffer_32));

	return le32_to_cpu(wl->buffer_32);
}

static inline void wl1251_write32(struct wl1251 *wl, int addr, u32 val)
{
	wl->buffer_32 = cpu_to_le32(val);
	wl->if_ops->write(wl, addr, &wl->buffer_32, sizeof(wl->buffer_32));
}

static inline u32 wl1251_read_elp(struct wl1251 *wl, int addr)
{
	u32 response;

	if (wl->if_ops->read_elp)
		wl->if_ops->read_elp(wl, addr, &response);
	else
		wl->if_ops->read(wl, addr, &response, sizeof(u32));

	return response;
}

static inline void wl1251_write_elp(struct wl1251 *wl, int addr, u32 val)
{
	if (wl->if_ops->write_elp)
		wl->if_ops->write_elp(wl, addr, val);
	else
		wl->if_ops->write(wl, addr, &val, sizeof(u32));
}

/* Memory target IO, address is translated to partition 0 */
void wl1251_mem_read(struct wl1251 *wl, int addr, void *buf, size_t len);
void wl1251_mem_write(struct wl1251 *wl, int addr, void *buf, size_t len);
u32 wl1251_mem_read32(struct wl1251 *wl, int addr);
void wl1251_mem_write32(struct wl1251 *wl, int addr, u32 val);
/* Registers IO */
u32 wl1251_reg_read32(struct wl1251 *wl, int addr);
void wl1251_reg_write32(struct wl1251 *wl, int addr, u32 val);

void wl1251_set_partition(struct wl1251 *wl,
			  u32 part_start, u32 part_size,
			  u32 reg_start,  u32 reg_size);

#endif
