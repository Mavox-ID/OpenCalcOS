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

#define MAX_DMA_CHANNELS 16

#define CH_PPI 			    0
#define CH_EMAC_RX 		    1
#define CH_EMAC_TX 		    2
#define CH_SPORT0_RX 		3
#define CH_SPORT0_TX 		4
#define CH_SPORT1_RX 		5
#define CH_SPORT1_TX 		6
#define CH_SPI 			    7
#define CH_UART0_RX 		8
#define CH_UART0_TX 		9
#define CH_UART1_RX 		10
#define CH_UART1_TX 		11

#define CH_MEM_STREAM0_DEST	12	 /* TX */
#define CH_MEM_STREAM0_SRC  	13	 /* RX */
#define CH_MEM_STREAM1_DEST	14	 /* TX */
#define CH_MEM_STREAM1_SRC 	15	 /* RX */

#endif
