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
#ifndef _LANTIQ_XWAY_IRQ_H__
#define _LANTIQ_XWAY_IRQ_H__

#define INT_NUM_IRQ0		8
#define INT_NUM_IM0_IRL0	(INT_NUM_IRQ0 + 0)
#define INT_NUM_IM1_IRL0	(INT_NUM_IRQ0 + 32)
#define INT_NUM_IM2_IRL0	(INT_NUM_IRQ0 + 64)
#define INT_NUM_IM3_IRL0	(INT_NUM_IRQ0 + 96)
#define INT_NUM_IM4_IRL0	(INT_NUM_IRQ0 + 128)
#define INT_NUM_IM_OFFSET	(INT_NUM_IM1_IRL0 - INT_NUM_IM0_IRL0)

#define LTQ_DMA_CH0_INT		(INT_NUM_IM2_IRL0)

#define MIPS_CPU_TIMER_IRQ	7

#define MAX_IM			5

#endif
