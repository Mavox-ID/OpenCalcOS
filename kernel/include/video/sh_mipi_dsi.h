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
#ifndef VIDEO_SH_MIPI_DSI_H
#define VIDEO_SH_MIPI_DSI_H

enum sh_mipi_dsi_data_fmt {
	MIPI_RGB888,
	MIPI_RGB565,
	MIPI_RGB666_LP,
	MIPI_RGB666,
	MIPI_BGR888,
	MIPI_BGR565,
	MIPI_BGR666_LP,
	MIPI_BGR666,
	MIPI_YUYV,
	MIPI_UYVY,
	MIPI_YUV420_L,
	MIPI_YUV420,
};

#define SH_MIPI_DSI_HSABM	(1 << 0)
#define SH_MIPI_DSI_HBPBM	(1 << 1)
#define SH_MIPI_DSI_HFPBM	(1 << 2)
#define SH_MIPI_DSI_BL2E	(1 << 3)
#define SH_MIPI_DSI_VSEE	(1 << 4)
#define SH_MIPI_DSI_HSEE	(1 << 5)
#define SH_MIPI_DSI_HSAE	(1 << 6)

#define SH_MIPI_DSI_HSbyteCLK	(1 << 24)
#define SH_MIPI_DSI_HS6divCLK	(1 << 25)
#define SH_MIPI_DSI_HS4divCLK	(1 << 26)

#define SH_MIPI_DSI_SYNC_PULSES_MODE	(SH_MIPI_DSI_VSEE | \
					 SH_MIPI_DSI_HSEE | \
					 SH_MIPI_DSI_HSAE)
#define SH_MIPI_DSI_SYNC_EVENTS_MODE	(0)
#define SH_MIPI_DSI_SYNC_BURST_MODE	(SH_MIPI_DSI_BL2E)

struct sh_mipi_dsi_info {
	enum sh_mipi_dsi_data_fmt	data_format;
	int				channel;
	int				lane;
	unsigned long			flags;
	u32				clksrc;
	u32				phyctrl; /* for extra setting */
	unsigned int			vsynw_offset;
	int	(*set_dot_clock)(struct platform_device *pdev,
				 void __iomem *base,
				 int enable);
};

#endif
