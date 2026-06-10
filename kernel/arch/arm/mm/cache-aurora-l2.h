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
#ifndef __ASM_ARM_HARDWARE_AURORA_L2_H
#define __ASM_ARM_HARDWARE_AURORA_L2_H

#define AURORA_SYNC_REG		    0x700
#define AURORA_RANGE_BASE_ADDR_REG  0x720
#define AURORA_FLUSH_PHY_ADDR_REG   0x7f0
#define AURORA_INVAL_RANGE_REG	    0x774
#define AURORA_CLEAN_RANGE_REG	    0x7b4
#define AURORA_FLUSH_RANGE_REG	    0x7f4

#define AURORA_ACR_REPLACEMENT_OFFSET	    27
#define AURORA_ACR_REPLACEMENT_MASK	     \
	(0x3 << AURORA_ACR_REPLACEMENT_OFFSET)
#define AURORA_ACR_REPLACEMENT_TYPE_WAYRR    \
	(0 << AURORA_ACR_REPLACEMENT_OFFSET)
#define AURORA_ACR_REPLACEMENT_TYPE_LFSR     \
	(1 << AURORA_ACR_REPLACEMENT_OFFSET)
#define AURORA_ACR_REPLACEMENT_TYPE_SEMIPLRU \
	(3 << AURORA_ACR_REPLACEMENT_OFFSET)

#define AURORA_ACR_FORCE_WRITE_POLICY_OFFSET	0
#define AURORA_ACR_FORCE_WRITE_POLICY_MASK	\
	(0x3 << AURORA_ACR_FORCE_WRITE_POLICY_OFFSET)
#define AURORA_ACR_FORCE_WRITE_POLICY_DIS	\
	(0 << AURORA_ACR_FORCE_WRITE_POLICY_OFFSET)
#define AURORA_ACR_FORCE_WRITE_BACK_POLICY	\
	(1 << AURORA_ACR_FORCE_WRITE_POLICY_OFFSET)
#define AURORA_ACR_FORCE_WRITE_THRO_POLICY	\
	(2 << AURORA_ACR_FORCE_WRITE_POLICY_OFFSET)

#define MAX_RANGE_SIZE		1024

#define AURORA_WAY_SIZE_SHIFT	2

#define AURORA_CTRL_FW		0x100

/* chose a number outside L2X0_CACHE_ID_PART_MASK to be sure to make
 * the distinction between a number coming from hardware and a number
 * coming from the device tree */
#define AURORA_CACHE_ID	       0x100

#endif /* __ASM_ARM_HARDWARE_AURORA_L2_H */
