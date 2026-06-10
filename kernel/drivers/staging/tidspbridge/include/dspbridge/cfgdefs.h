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
#ifndef CFGDEFS_
#define CFGDEFS_

/* Host Resources: */
#define CFG_MAXMEMREGISTERS     9

/* IRQ flag */
#define CFG_IRQSHARED           0x01	/* IRQ can be shared */

/* A platform-related device handle: */
struct cfg_devnode;

/*
 *  Host resource structure.
 */
struct cfg_hostres {
	u32 num_mem_windows;	/* Set to default */
	/* This is the base.memory */
	u32 mem_base[CFG_MAXMEMREGISTERS];	/* shm virtual address */
	u32 mem_length[CFG_MAXMEMREGISTERS];	/* Length of the Base */
	u32 mem_phys[CFG_MAXMEMREGISTERS];	/* shm Physical address */
	u8 birq_registers;	/* IRQ Number */
	u8 birq_attrib;		/* IRQ Attribute */
	u32 offset_for_monitor;	/* The Shared memory starts from
					 * mem_base + this offset */
	/*
	 *  Info needed by NODE for allocating channels to communicate with RMS:
	 *      chnl_offset:       Offset of RMS channels. Lower channels are
	 *                          reserved.
	 *      chnl_buf_size:      Size of channel buffer to send to RMS
	 *      num_chnls:		Total number of channels
	 *      			(including reserved).
	 */
	u32 chnl_offset;
	u32 chnl_buf_size;
	u32 num_chnls;
	void __iomem *per_base;
	void __iomem *per_pm_base;
	void __iomem *core_pm_base;
	void __iomem *dmmu_base;
};

#endif /* CFGDEFS_ */
