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
#ifndef _BEEP_METRONOMEFB_H_
#define _BEEP_METRONOMEFB_H_

/* command structure used by metronome controller */
struct metromem_cmd {
	u16 opcode;
	u16 args[((64-2)/2)];
	u16 csum;
};

/* struct used by metronome. board specific stuff comes from *board */
struct metronomefb_par {
	struct metromem_cmd *metromem_cmd;
	unsigned char *metromem_wfm;
	unsigned char *metromem_img;
	u16 *metromem_img_csum;
	u16 *csum_table;
	dma_addr_t metromem_dma;
	struct fb_info *info;
	struct metronome_board *board;
	wait_queue_head_t waitq;
	u8 frame_count;
	int extra_size;
	int dt;
};

/* board specific routines and data */
struct metronome_board {
	struct module *owner; /* the platform device */
	void (*set_rst)(struct metronomefb_par *, int);
	void (*set_stdby)(struct metronomefb_par *, int);
	void (*cleanup)(struct metronomefb_par *);
	int (*met_wait_event)(struct metronomefb_par *);
	int (*met_wait_event_intr)(struct metronomefb_par *);
	int (*setup_irq)(struct fb_info *);
	int (*setup_fb)(struct metronomefb_par *);
	int (*setup_io)(struct metronomefb_par *);
	int (*get_panel_type)(void);
	unsigned char *metromem;
	int fw;
	int fh;
	int wfm_size;
	struct fb_info *host_fbinfo; /* the host LCD controller's fbi */
};

#endif
