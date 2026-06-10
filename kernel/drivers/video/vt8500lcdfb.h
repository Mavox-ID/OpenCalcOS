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
struct vt8500lcd_info {
	struct fb_info		fb;
	void __iomem		*regbase;
	void __iomem		*palette_cpu;
	dma_addr_t		palette_phys;
	size_t			palette_size;
	wait_queue_head_t	wait;
};

static int bpp_values[] = {
	1,
	2,
	4,
	8,
	12,
	16,
	18,
	24,
};
