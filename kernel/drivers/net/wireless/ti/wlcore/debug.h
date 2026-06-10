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
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <beep/bitops.h>
#include <beep/printk.h>

#define DRIVER_NAME "wlcore"
#define DRIVER_PREFIX DRIVER_NAME ": "

enum {
	DEBUG_NONE	= 0,
	DEBUG_IRQ	= BIT(0),
	DEBUG_SPI	= BIT(1),
	DEBUG_BOOT	= BIT(2),
	DEBUG_MAILBOX	= BIT(3),
	DEBUG_TESTMODE	= BIT(4),
	DEBUG_EVENT	= BIT(5),
	DEBUG_TX	= BIT(6),
	DEBUG_RX	= BIT(7),
	DEBUG_SCAN	= BIT(8),
	DEBUG_CRYPT	= BIT(9),
	DEBUG_PSM	= BIT(10),
	DEBUG_MAC80211	= BIT(11),
	DEBUG_CMD	= BIT(12),
	DEBUG_ACX	= BIT(13),
	DEBUG_SDIO	= BIT(14),
	DEBUG_FILTERS   = BIT(15),
	DEBUG_ADHOC     = BIT(16),
	DEBUG_AP	= BIT(17),
	DEBUG_PROBE	= BIT(18),
	DEBUG_IO	= BIT(19),
	DEBUG_MASTER	= (DEBUG_ADHOC | DEBUG_AP),
	DEBUG_ALL	= ~0,
};

extern u32 wl12xx_debug_level;

#define DEBUG_DUMP_LIMIT 1024

#define wl1271_error(fmt, arg...) \
	pr_err(DRIVER_PREFIX "ERROR " fmt "\n", ##arg)

#define wl1271_warning(fmt, arg...) \
	pr_warning(DRIVER_PREFIX "WARNING " fmt "\n", ##arg)

#define wl1271_notice(fmt, arg...) \
	pr_info(DRIVER_PREFIX fmt "\n", ##arg)

#define wl1271_info(fmt, arg...) \
	pr_info(DRIVER_PREFIX fmt "\n", ##arg)

/* define the debug macro differently if dynamic debug is supported */
#if defined(CONFIG_DYNAMIC_DEBUG)
#define wl1271_debug(level, fmt, arg...) \
	do { \
		if (unlikely(level & wl12xx_debug_level)) \
			dynamic_pr_debug(DRIVER_PREFIX fmt "\n", ##arg); \
	} while (0)
#else
#define wl1271_debug(level, fmt, arg...) \
	do { \
		if (unlikely(level & wl12xx_debug_level)) \
			printk(KERN_DEBUG pr_fmt(DRIVER_PREFIX fmt "\n"), \
			       ##arg); \
	} while (0)
#endif

/* TODO: use pr_debug_hex_dump when it becomes available */
#define wl1271_dump(level, prefix, buf, len)	\
	do { \
		if (level & wl12xx_debug_level) \
			print_hex_dump(KERN_DEBUG, DRIVER_PREFIX prefix, \
				       DUMP_PREFIX_OFFSET, 16, 1,	\
				       buf,				\
				       min_t(size_t, len, DEBUG_DUMP_LIMIT), \
				       0);				\
	} while (0)

#define wl1271_dump_ascii(level, prefix, buf, len)	\
	do { \
		if (level & wl12xx_debug_level) \
			print_hex_dump(KERN_DEBUG, DRIVER_PREFIX prefix, \
				       DUMP_PREFIX_OFFSET, 16, 1,	\
				       buf,				\
				       min_t(size_t, len, DEBUG_DUMP_LIMIT), \
				       true);				\
	} while (0)

#endif /* __DEBUG_H__ */
