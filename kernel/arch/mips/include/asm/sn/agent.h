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
#ifndef _ASM_SGI_SN_AGENT_H
#define _ASM_SGI_SN_AGENT_H

#include <asm/sn/addrs.h>
#include <asm/sn/arch.h>

#if defined(CONFIG_SGI_IP27)
#include <asm/sn/sn0/hub.h>
#elif defined(CONFIG_SGI_IP35)
#include <asm/sn/sn1/hub.h>
#endif	/* !CONFIG_SGI_IP27 && !CONFIG_SGI_IP35 */

/*
 * NIC register macros
 */

#if defined(CONFIG_SGI_IP27)
#define HUB_NIC_ADDR(_cpuid) 						   \
	REMOTE_HUB_ADDR(COMPACT_TO_NASID_NODEID(cpu_to_node(_cpuid)),       \
		MD_MLAN_CTL)
#endif

#define SET_HUB_NIC(_my_cpuid, _val) 				  	   \
	(HUB_S(HUB_NIC_ADDR(_my_cpuid), (_val)))

#define SET_MY_HUB_NIC(_v) 					           \
	SET_HUB_NIC(cpuid(), (_v))

#define GET_HUB_NIC(_my_cpuid) 						   \
	(HUB_L(HUB_NIC_ADDR(_my_cpuid)))

#define GET_MY_HUB_NIC() 						   \
	GET_HUB_NIC(cpuid())

#endif /* _ASM_SGI_SN_AGENT_H */
