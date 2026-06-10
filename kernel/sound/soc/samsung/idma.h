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
#ifndef __SND_SOC_SAMSUNG_IDMA_H_
#define __SND_SOC_SAMSUNG_IDMA_H_

extern void idma_reg_addr_init(void __iomem *regs, dma_addr_t addr);

/* dma_state */
#define LPAM_DMA_STOP	0
#define LPAM_DMA_START	1

#define MAX_IDMA_PERIOD (128 * 1024)
#define MAX_IDMA_BUFFER (160 * 1024)

#endif /* __SND_SOC_SAMSUNG_IDMA_H_ */
