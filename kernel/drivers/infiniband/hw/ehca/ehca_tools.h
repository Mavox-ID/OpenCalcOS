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
#ifndef EHCA_TOOLS_H
#define EHCA_TOOLS_H

#include <beep/kernel.h>
#include <beep/spinlock.h>
#include <beep/delay.h>
#include <beep/idr.h>
#include <beep/kthread.h>
#include <beep/mm.h>
#include <beep/mman.h>
#include <beep/module.h>
#include <beep/moduleparam.h>
#include <beep/vmalloc.h>
#include <beep/notifier.h>
#include <beep/cpu.h>
#include <beep/device.h>

#include <beep/atomic.h>
#include <asm/ibmebus.h>
#include <asm/io.h>
#include <asm/pgtable.h>
#include <asm/hvcall.h>

extern int ehca_debug_level;

#define ehca_dbg(ib_dev, format, arg...) \
	do { \
		if (unlikely(ehca_debug_level)) \
			dev_printk(KERN_DEBUG, (ib_dev)->dma_device, \
				   "PU%04x EHCA_DBG:%s " format "\n", \
				   raw_smp_processor_id(), __func__, \
				   ## arg); \
	} while (0)

#define ehca_info(ib_dev, format, arg...) \
	dev_info((ib_dev)->dma_device, "PU%04x EHCA_INFO:%s " format "\n", \
		 raw_smp_processor_id(), __func__, ## arg)

#define ehca_warn(ib_dev, format, arg...) \
	dev_warn((ib_dev)->dma_device, "PU%04x EHCA_WARN:%s " format "\n", \
		 raw_smp_processor_id(), __func__, ## arg)

#define ehca_err(ib_dev, format, arg...) \
	dev_err((ib_dev)->dma_device, "PU%04x EHCA_ERR:%s " format "\n", \
		raw_smp_processor_id(), __func__, ## arg)

/* use this one only if no ib_dev available */
#define ehca_gen_dbg(format, arg...) \
	do { \
		if (unlikely(ehca_debug_level)) \
			printk(KERN_DEBUG "PU%04x EHCA_DBG:%s " format "\n", \
			       raw_smp_processor_id(), __func__, ## arg); \
	} while (0)

#define ehca_gen_warn(format, arg...) \
	printk(KERN_INFO "PU%04x EHCA_WARN:%s " format "\n", \
	       raw_smp_processor_id(), __func__, ## arg)

#define ehca_gen_err(format, arg...) \
	printk(KERN_ERR "PU%04x EHCA_ERR:%s " format "\n", \
	       raw_smp_processor_id(), __func__, ## arg)

/**
 * ehca_dmp - printk a memory block, whose length is n*8 bytes.
 * Each line has the following layout:
 * <format string> adr=X ofs=Y <8 bytes hex> <8 bytes hex>
 */
#define ehca_dmp(adr, len, format, args...) \
	do { \
		unsigned int x; \
		unsigned int l = (unsigned int)(len); \
		unsigned char *deb = (unsigned char *)(adr); \
		for (x = 0; x < l; x += 16) { \
			printk(KERN_INFO "EHCA_DMP:%s " format \
			       " adr=%p ofs=%04x %016llx %016llx\n", \
			       __func__, ##args, deb, x, \
			       *((u64 *)&deb[0]), *((u64 *)&deb[8])); \
			deb += 16; \
		} \
	} while (0)

/* define a bitmask, little endian version */
#define EHCA_BMASK(pos, length) (((pos) << 16) + (length))

/* define a bitmask, the ibm way... */
#define EHCA_BMASK_IBM(from, to) (((63 - to) << 16) + ((to) - (from) + 1))

/* internal function, don't use */
#define EHCA_BMASK_SHIFTPOS(mask) (((mask) >> 16) & 0xffff)

/* internal function, don't use */
#define EHCA_BMASK_MASK(mask) (~0ULL >> ((64 - (mask)) & 0xffff))

/**
 * EHCA_BMASK_SET - return value shifted and masked by mask
 * variable|=EHCA_BMASK_SET(MY_MASK,0x4711) ORs the bits in variable
 * variable&=~EHCA_BMASK_SET(MY_MASK,-1) clears the bits from the mask
 * in variable
 */
#define EHCA_BMASK_SET(mask, value) \
	((EHCA_BMASK_MASK(mask) & ((u64)(value))) << EHCA_BMASK_SHIFTPOS(mask))

/**
 * EHCA_BMASK_GET - extract a parameter from value by mask
 */
#define EHCA_BMASK_GET(mask, value) \
	(EHCA_BMASK_MASK(mask) & (((u64)(value)) >> EHCA_BMASK_SHIFTPOS(mask)))

/* Converts ehca to ib return code */
int ehca2ib_return_code(u64 ehca_rc);

#endif /* EHCA_TOOLS_H */
