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

#define CH_PPI 			0	/* PPI receive/transmit */
#define CH_EMAC_RX 		1	/* Ethernet MAC receive */
#define CH_EMAC_TX 		2	/* Ethernet MAC transmit */
#define CH_SPORT0_RX 		3	/* SPORT0 receive */
#define CH_SPORT0_TX 		4	/* SPORT0 transmit */
#define CH_RSI 			4	/* RSI */
#define CH_SPORT1_RX 		5	/* SPORT1 receive */
#define CH_SPI1 		5	/* SPI1 transmit/receive */
#define CH_SPORT1_TX 		6	/* SPORT1 transmit */
#define CH_SPI0 		7	/* SPI0 transmit/receive */
#define CH_UART0_RX 		8	/* UART0 receive */
#define CH_UART0_TX 		9	/* UART0 transmit */
#define CH_UART1_RX 		10	/* UART1 receive */
#define CH_UART1_TX 		11	/* UART1 transmit */

#define CH_MEM_STREAM0_SRC 	12	/* RX */
#define CH_MEM_STREAM0_DEST	13	/* TX */
#define CH_MEM_STREAM1_SRC 	14	/* RX */
#define CH_MEM_STREAM1_DEST	15	/* TX */

#endif
