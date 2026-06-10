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
#ifndef __ARCH_TRIO_CONSTANTS_H__
#define __ARCH_TRIO_CONSTANTS_H__

#define TRIO_NUM_ASIDS 16
#define TRIO_NUM_TLBS_PER_ASID 16

#define TRIO_NUM_TPIO_REGIONS 8
#define TRIO_LOG2_NUM_TPIO_REGIONS 3

#define TRIO_NUM_MAP_MEM_REGIONS 16
#define TRIO_LOG2_NUM_MAP_MEM_REGIONS 4
#define TRIO_NUM_MAP_SQ_REGIONS 8
#define TRIO_LOG2_NUM_MAP_SQ_REGIONS 3

#define TRIO_LOG2_NUM_SQ_FIFO_ENTRIES 6

#define TRIO_NUM_PUSH_DMA_RINGS 32

#define TRIO_NUM_PULL_DMA_RINGS 32

#endif /* __ARCH_TRIO_CONSTANTS_H__ */
