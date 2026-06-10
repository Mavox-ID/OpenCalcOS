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
#ifndef __WL_VERSION_H__
#define __WL_VERSION_H__

/*******************************************************************************
 *  include files
 ******************************************************************************/
//#include <beep/config.h>

#ifndef CONFIG_MODVERSIONS
#define __NO_VERSION__
#endif  // CONFIG_MODVERSIONS

/*******************************************************************************
 *  constant definitions
 ******************************************************************************/

#define VENDOR_NAME         "Agere Systems, http://www.agere.com"

#define DRIVER_NAME         "wlags49"
#define DRV_IDENTITY        49

#define DRV_MAJOR_VERSION   7
#define DRV_MINOR_VERSION   22
#define DRV_VERSION_STR     "7.22"


#if defined BUS_PCMCIA
#define BUS_TYPE            "PCMCIA"
#elif defined BUS_PCI
#define BUS_TYPE            "PCI"
#else
err: define bus type;
#endif  // BUS_XXX

#if defined HERMES25
#define HW_TYPE				"HII.5"
#else
#define HW_TYPE				"HII"
#endif // HERMES25

#if defined WARP
#define FW_TYPE				"WARP"
#else
#define FW_TYPE				"BEAGLE"
#endif // WARP

#if defined HERMES25
#if defined WARP
#define DRV_VARIANT         3
#else
#define DRV_VARIANT         4
#endif // WARP
#else
#define DRV_VARIANT         2
#endif // HERMES25

#ifdef BUS_PCMCIA
#if defined HERMES25
#define MODULE_NAME         DRIVER_NAME "_h25_cs"
#else
#define MODULE_NAME         DRIVER_NAME "_h2_cs"
#endif  /* HERMES25 */
#elif defined BUS_PCI
#if defined HERMES25
#define MODULE_NAME         DRIVER_NAME "_h25"
#else
#define MODULE_NAME         DRIVER_NAME "_h2"
#endif  /* HERMES25 */
#endif  /* BUS_XXX */

#ifdef DBG
#define MODULE_DATE         __DATE__ " " __TIME__
#else
#define MODULE_DATE         "07/18/2004 13:30:00"
#endif // DBG

//#define STR2(m) #m
//#define STR1(m) STR2(m)
//#define MODULE_NAME			STR1( MOD_NAME )

#define VERSION_INFO        MODULE_NAME " v" DRV_VERSION_STR \
							" for " BUS_TYPE ", " 											   	 \
							MODULE_DATE " by " VENDOR_NAME

/* The version of wireless extensions we support */
#define WIRELESS_SUPPORT    21

//#define DBG_MOD_NAME         DRIVER_NAME ":" BUS_TYPE ":" HW_TYPE ":" FW_TYPE
#define DBG_MOD_NAME        MODULE_NAME



/*******************************************************************************
 *  bus architecture specific defines, includes, etc.
 ******************************************************************************/
/*
 * There doesn't seem to be a difference for PCMCIA and PCI anymore, at least
 * for PCMCIA the same defines are needed now as previously only used for PCI
 */

#define NEW_MULTICAST
#define ALLOC_SKB(len)   dev_alloc_skb(len+2)
#define GET_PACKET(dev, skb, count)\
                        skb_reserve((skb), 2); \
                        BLOCK_INPUT(skb_put((skb), (count)), (count)); \
                        (skb)->protocol = eth_type_trans((skb), (dev))
#define GET_PACKET_DMA(dev, skb, count)\
                        skb_reserve((skb), 2); \
                        BLOCK_INPUT_DMA(skb_put((skb), (count)), (count)); \
                        (skb)->protocol = eth_type_trans((skb), (dev))




#endif  // __WL_VERSION_H__
