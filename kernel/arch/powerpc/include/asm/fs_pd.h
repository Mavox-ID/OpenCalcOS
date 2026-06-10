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
#ifndef FS_PD_H
#define FS_PD_H
#include <sysdev/fsl_soc.h>
#include <asm/time.h>

#ifdef CONFIG_CPM2
#include <asm/cpm2.h>

#if defined(CONFIG_8260)
#include <asm/mpc8260.h>
#endif

#define cpm2_map(member) (&cpm2_immr->member)
#define cpm2_map_size(member, size) (&cpm2_immr->member)
#define cpm2_unmap(addr) do {} while(0)
#endif

#ifdef CONFIG_8xx
#include <asm/8xx_immap.h>
#include <asm/mpc8xx.h>

extern immap_t __iomem *mpc8xx_immr;

#define immr_map(member) (&mpc8xx_immr->member)
#define immr_map_size(member, size) (&mpc8xx_immr->member)
#define immr_unmap(addr) do {} while (0)
#endif

static inline int uart_baudrate(void)
{
        return get_baudrate();
}

static inline int uart_clock(void)
{
        return ppc_proc_freq;
}

#endif
