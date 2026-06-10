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
#ifndef __MDFLD_DSI_PKG_SENDER_H__
#define __MDFLD_DSI_PKG_SENDER_H__

#include <beep/kthread.h>

#define MDFLD_MAX_DCS_PARAM	8

struct mdfld_dsi_pkg_sender {
	struct drm_device *dev;
	struct mdfld_dsi_connector *dsi_connector;
	u32 status;
	u32 panel_mode;

	int pipe;

	spinlock_t lock;

	u32 pkg_num;

	/* Registers */
	u32 dpll_reg;
	u32 dspcntr_reg;
	u32 pipeconf_reg;
	u32 pipestat_reg;
	u32 dsplinoff_reg;
	u32 dspsurf_reg;

	u32 mipi_intr_stat_reg;
	u32 mipi_lp_gen_data_reg;
	u32 mipi_hs_gen_data_reg;
	u32 mipi_lp_gen_ctrl_reg;
	u32 mipi_hs_gen_ctrl_reg;
	u32 mipi_gen_fifo_stat_reg;
	u32 mipi_data_addr_reg;
	u32 mipi_data_len_reg;
	u32 mipi_cmd_addr_reg;
	u32 mipi_cmd_len_reg;
};

/* DCS definitions */
#define DCS_SOFT_RESET			0x01
#define DCS_ENTER_SLEEP_MODE		0x10
#define DCS_EXIT_SLEEP_MODE		0x11
#define DCS_SET_DISPLAY_OFF		0x28
#define DCS_SET_DISPLAY_ON		0x29
#define DCS_SET_COLUMN_ADDRESS		0x2a
#define DCS_SET_PAGE_ADDRESS		0x2b
#define DCS_WRITE_MEM_START		0x2c
#define DCS_SET_TEAR_OFF		0x34
#define DCS_SET_TEAR_ON			0x35

extern int mdfld_dsi_pkg_sender_init(struct mdfld_dsi_connector *dsi_connector,
					int pipe);
extern void mdfld_dsi_pkg_sender_destroy(struct mdfld_dsi_pkg_sender *sender);
int mdfld_dsi_send_mcs_short(struct mdfld_dsi_pkg_sender *sender, u8 cmd,
					u8 param, u8 param_num, bool hs);
int mdfld_dsi_send_mcs_long(struct mdfld_dsi_pkg_sender *sender, u8 *data,
					u32 len, bool hs);
int mdfld_dsi_send_gen_short(struct mdfld_dsi_pkg_sender *sender, u8 param0,
					u8 param1, u8 param_num, bool hs);
int mdfld_dsi_send_gen_long(struct mdfld_dsi_pkg_sender *sender, u8 *data,
					u32 len, bool hs);
/* Read interfaces */
int mdfld_dsi_read_mcs(struct mdfld_dsi_pkg_sender *sender, u8 cmd,
		u32 *data, u16 len, bool hs);

#endif
