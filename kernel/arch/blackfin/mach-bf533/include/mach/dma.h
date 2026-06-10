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
#ifndef _MACH_DMA_H_
#define _MACH_DMA_H_

#define MAX_DMA_CHANNELS 12

#define CH_PPI          0
#define CH_SPORT0_RX    1
#define CH_SPORT0_TX    2
#define CH_SPORT1_RX    3
#define CH_SPORT1_TX    4
#define CH_SPI          5
#define CH_UART0_RX     6
#define CH_UART0_TX     7
#define CH_MEM_STREAM0_DEST     8	 /* TX */
#define CH_MEM_STREAM0_SRC      9	 /* RX */
#define CH_MEM_STREAM1_DEST     10	 /* TX */
#define CH_MEM_STREAM1_SRC      11	 /* RX */

#endif
