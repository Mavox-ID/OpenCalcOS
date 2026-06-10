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
#ifndef _CS5536_MFGPT_H
#define _CS5536_MFGPT_H

#include <cs5536/cs5536.h>
#include <cs5536/cs5536_pci.h>

#ifdef CONFIG_CS5536_MFGPT
extern void setup_mfgpt0_timer(void);
extern void disable_mfgpt0_counter(void);
extern void enable_mfgpt0_counter(void);
#else
static inline void __maybe_unused setup_mfgpt0_timer(void)
{
}
static inline void __maybe_unused disable_mfgpt0_counter(void)
{
}
static inline void __maybe_unused enable_mfgpt0_counter(void)
{
}
#endif

#define MFGPT_TICK_RATE 14318000
#define COMPARE  ((MFGPT_TICK_RATE + HZ/2) / HZ)

#define MFGPT_BASE	mfgpt_base
#define MFGPT0_CMP2	(MFGPT_BASE + 2)
#define MFGPT0_CNT	(MFGPT_BASE + 4)
#define MFGPT0_SETUP	(MFGPT_BASE + 6)

#endif /*!_CS5536_MFGPT_H */
