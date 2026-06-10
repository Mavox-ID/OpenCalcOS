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
#ifdef __KERNEL__
#ifndef __ASM_POWERPC_MPC8260_H__
#define __ASM_POWERPC_MPC8260_H__

#define MPC82XX_BCR_PLDP 0x00800000 /* Pipeline Maximum Depth */

#ifdef CONFIG_8260

#if defined(CONFIG_PQ2ADS) || defined (CONFIG_PQ2FADS)
#include <platforms/82xx/pq2ads.h>
#endif

#ifdef CONFIG_PCI_8260
#include <platforms/82xx/m82xx_pci.h>
#endif

#endif /* CONFIG_8260 */
#endif /* !__ASM_POWERPC_MPC8260_H__ */
#endif /* __KERNEL__ */
