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
#ifndef _UAPI__BFIN_ASM_FIXED_CODE_H__
#define _UAPI__BFIN_ASM_FIXED_CODE_H__


#ifndef CONFIG_PHY_RAM_BASE_ADDRESS
#define CONFIG_PHY_RAM_BASE_ADDRESS	0x0
#endif

#define FIXED_CODE_START	(CONFIG_PHY_RAM_BASE_ADDRESS + 0x400)

#define SIGRETURN_STUB		(CONFIG_PHY_RAM_BASE_ADDRESS + 0x400)

#define ATOMIC_SEQS_START	(CONFIG_PHY_RAM_BASE_ADDRESS + 0x410)

#define ATOMIC_XCHG32		(CONFIG_PHY_RAM_BASE_ADDRESS + 0x410)
#define ATOMIC_CAS32		(CONFIG_PHY_RAM_BASE_ADDRESS + 0x420)
#define ATOMIC_ADD32		(CONFIG_PHY_RAM_BASE_ADDRESS + 0x430)
#define ATOMIC_SUB32		(CONFIG_PHY_RAM_BASE_ADDRESS + 0x440)
#define ATOMIC_IOR32		(CONFIG_PHY_RAM_BASE_ADDRESS + 0x450)
#define ATOMIC_AND32		(CONFIG_PHY_RAM_BASE_ADDRESS + 0x460)
#define ATOMIC_XOR32		(CONFIG_PHY_RAM_BASE_ADDRESS + 0x470)

#define ATOMIC_SEQS_END		(CONFIG_PHY_RAM_BASE_ADDRESS + 0x480)

#define SAFE_USER_INSTRUCTION   (CONFIG_PHY_RAM_BASE_ADDRESS + 0x480)

#define FIXED_CODE_END		(CONFIG_PHY_RAM_BASE_ADDRESS + 0x490)

#endif /* _UAPI__BFIN_ASM_FIXED_CODE_H__ */
