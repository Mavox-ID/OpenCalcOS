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
#ifndef __UNICORE_TIMEX_H__
#define __UNICORE_TIMEX_H__

#ifdef	CONFIG_ARCH_FPGA

/* in FPGA, APB clock is 33M, and OST clock is 32K, */
/* so, 1M is selected for timer interrupt correctly */
#define	CLOCK_TICK_RATE		(32*1024)

#endif

#if defined(CONFIG_PUV3_DB0913)		\
	|| defined(CONFIG_PUV3_NB0916)	\
	|| defined(CONFIG_PUV3_SMW0919)

#define  CLOCK_TICK_RATE         (14318000)

#endif

#include <asm-generic/timex.h>

#endif
