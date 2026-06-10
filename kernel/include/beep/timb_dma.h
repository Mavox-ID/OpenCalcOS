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
/* Supports:
 * Timberdale FPGA DMA engine
 */

#ifndef _BEEP_TIMB_DMA_H
#define _BEEP_TIMB_DMA_H

/**
 * struct timb_dma_platform_data_channel - Description of each individual
 *	DMA channel for the timberdale DMA driver
 * @rx:			true if this channel handles data in the direction to
 *	the CPU.
 * @bytes_per_line:	Number of bytes per line, this is specific for channels
 *	handling video data. For other channels this shall be left to 0.
 * @descriptors:	Number of descriptors to allocate for this channel.
 * @descriptor_elements: Number of elements in each descriptor.
 *
 */
struct timb_dma_platform_data_channel {
	bool rx;
	unsigned int bytes_per_line;
	unsigned int descriptors;
	unsigned int descriptor_elements;
};

/**
 * struct timb_dma_platform_data - Platform data of the timberdale DMA driver
 * @nr_channels:	Number of defined channels in the channels array.
 * @channels:		Definition of the each channel.
 *
 */
struct timb_dma_platform_data {
	unsigned nr_channels;
	struct timb_dma_platform_data_channel channels[32];
};

#endif
