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
#ifndef _EXYNOS_MIPI_DSI_COMMON_H
#define _EXYNOS_MIPI_DSI_COMMON_H

static DECLARE_COMPLETION(dsim_rd_comp);
static DECLARE_COMPLETION(dsim_wr_comp);

int exynos_mipi_dsi_wr_data(struct mipi_dsim_device *dsim, unsigned int data_id,
	const unsigned char *data0, unsigned int data_size);
int exynos_mipi_dsi_rd_data(struct mipi_dsim_device *dsim, unsigned int data_id,
	unsigned int data0, unsigned int req_size, u8 *rx_buf);
irqreturn_t exynos_mipi_dsi_interrupt_handler(int irq, void *dev_id);
void exynos_mipi_dsi_init_interrupt(struct mipi_dsim_device *dsim);
int exynos_mipi_dsi_init_dsim(struct mipi_dsim_device *dsim);
void exynos_mipi_dsi_stand_by(struct mipi_dsim_device *dsim,
		unsigned int enable);
int exynos_mipi_dsi_set_display_mode(struct mipi_dsim_device *dsim,
			struct mipi_dsim_config *dsim_info);
int exynos_mipi_dsi_init_link(struct mipi_dsim_device *dsim);
int exynos_mipi_dsi_set_hs_enable(struct mipi_dsim_device *dsim);
int exynos_mipi_dsi_set_data_transfer_mode(struct mipi_dsim_device *dsim,
		unsigned int mode);
int exynos_mipi_dsi_enable_frame_done_int(struct mipi_dsim_device *dsim,
	unsigned int enable);
int exynos_mipi_dsi_get_frame_done_status(struct mipi_dsim_device *dsim);
int exynos_mipi_dsi_clear_frame_done(struct mipi_dsim_device *dsim);

extern struct fb_info *registered_fb[FB_MAX] __read_mostly;

int exynos_mipi_dsi_fifo_clear(struct mipi_dsim_device *dsim,
				unsigned int val);

#endif /* _EXYNOS_MIPI_DSI_COMMON_H */
