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
#ifndef _BEEP_BROADSHEETFB_H_
#define _BEEP_BROADSHEETFB_H_

/* Broadsheet command defines */
#define BS_CMD_INIT_SYS_RUN	0x06
#define BS_CMD_INIT_DSPE_CFG	0x09
#define BS_CMD_INIT_DSPE_TMG	0x0A
#define BS_CMD_INIT_ROTMODE	0x0B
#define BS_CMD_RD_REG		0x10
#define BS_CMD_WR_REG		0x11
#define BS_CMD_LD_IMG		0x20
#define BS_CMD_LD_IMG_AREA	0x22
#define BS_CMD_LD_IMG_END	0x23
#define BS_CMD_WAIT_DSPE_TRG	0x28
#define BS_CMD_WAIT_DSPE_FREND	0x29
#define BS_CMD_RD_WFM_INFO	0x30
#define BS_CMD_UPD_INIT		0x32
#define BS_CMD_UPD_FULL		0x33
#define BS_CMD_UPD_GDRV_CLR	0x37

/* Broadsheet register interface defines */
#define BS_REG_REV		0x00
#define BS_REG_PRC		0x02

/* Broadsheet pin interface specific defines */
#define BS_CS	0x01
#define BS_DC 	0x02
#define BS_WR 	0x03

/* Broadsheet IO interface specific defines */
#define BS_MMIO_CMD	0x01
#define BS_MMIO_DATA	0x02

/* struct used by broadsheet. board specific stuff comes from *board */
struct broadsheetfb_par {
	struct fb_info *info;
	struct broadsheet_board *board;
	void (*write_reg)(struct broadsheetfb_par *, u16 reg, u16 val);
	u16 (*read_reg)(struct broadsheetfb_par *, u16 reg);
	wait_queue_head_t waitq;
	int panel_index;
	struct mutex io_lock;
};

/* board specific routines */
struct broadsheet_board {
	struct module *owner;
	int (*init)(struct broadsheetfb_par *);
	int (*wait_for_rdy)(struct broadsheetfb_par *);
	void (*cleanup)(struct broadsheetfb_par *);
	int (*get_panel_type)(void);
	int (*setup_irq)(struct fb_info *);

	/* Functions for boards that use GPIO */
	void (*set_ctl)(struct broadsheetfb_par *, unsigned char, u8);
	void (*set_hdb)(struct broadsheetfb_par *, u16);
	u16 (*get_hdb)(struct broadsheetfb_par *);

	/* Functions for boards that have specialized MMIO */
	void (*mmio_write)(struct broadsheetfb_par *, int type, u16);
	u16 (*mmio_read)(struct broadsheetfb_par *);
};
#endif
