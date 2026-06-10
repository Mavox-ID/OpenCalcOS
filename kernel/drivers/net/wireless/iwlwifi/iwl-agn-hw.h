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
/*
 * Please use this file (iwl-agn-hw.h) only for hardware-related definitions.
 */

#ifndef __iwl_agn_hw_h__
#define __iwl_agn_hw_h__

#define IWLAGN_RTC_INST_LOWER_BOUND		(0x000000)
#define IWLAGN_RTC_INST_UPPER_BOUND		(0x020000)

#define IWLAGN_RTC_DATA_LOWER_BOUND		(0x800000)
#define IWLAGN_RTC_DATA_UPPER_BOUND		(0x80C000)

#define IWLAGN_RTC_INST_SIZE (IWLAGN_RTC_INST_UPPER_BOUND - \
				IWLAGN_RTC_INST_LOWER_BOUND)
#define IWLAGN_RTC_DATA_SIZE (IWLAGN_RTC_DATA_UPPER_BOUND - \
				IWLAGN_RTC_DATA_LOWER_BOUND)

#define IWL60_RTC_INST_LOWER_BOUND		(0x000000)
#define IWL60_RTC_INST_UPPER_BOUND		(0x040000)
#define IWL60_RTC_DATA_LOWER_BOUND		(0x800000)
#define IWL60_RTC_DATA_UPPER_BOUND		(0x814000)
#define IWL60_RTC_INST_SIZE \
	(IWL60_RTC_INST_UPPER_BOUND - IWL60_RTC_INST_LOWER_BOUND)
#define IWL60_RTC_DATA_SIZE \
	(IWL60_RTC_DATA_UPPER_BOUND - IWL60_RTC_DATA_LOWER_BOUND)

/* RSSI to dBm */
#define IWLAGN_RSSI_OFFSET	44

#define IWLAGN_DEFAULT_TX_RETRY			15
#define IWLAGN_MGMT_DFAULT_RETRY_LIMIT		3
#define IWLAGN_RTS_DFAULT_RETRY_LIMIT		60
#define IWLAGN_BAR_DFAULT_RETRY_LIMIT		60
#define IWLAGN_LOW_RETRY_LIMIT			7

/* Limit range of txpower output target to be between these values */
#define IWLAGN_TX_POWER_TARGET_POWER_MIN	(0)	/* 0 dBm: 1 milliwatt */
#define IWLAGN_TX_POWER_TARGET_POWER_MAX	(16)	/* 16 dBm */

/* EEPROM */
#define IWLAGN_EEPROM_IMG_SIZE		2048
/* OTP */
/* lower blocks contain EEPROM image and calibration data */
#define OTP_LOW_IMAGE_SIZE		(2 * 512 * sizeof(u16)) /* 2 KB */
/* high blocks contain PAPD data */
#define OTP_HIGH_IMAGE_SIZE_6x00        (6 * 512 * sizeof(u16)) /* 6 KB */
#define OTP_HIGH_IMAGE_SIZE_1000        (0x200 * sizeof(u16)) /* 1024 bytes */
#define OTP_MAX_LL_ITEMS_1000		(3)	/* OTP blocks for 1000 */
#define OTP_MAX_LL_ITEMS_6x00		(4)	/* OTP blocks for 6x00 */
#define OTP_MAX_LL_ITEMS_6x50		(7)	/* OTP blocks for 6x50 */
#define OTP_MAX_LL_ITEMS_2x00		(4)	/* OTP blocks for 2x00 */


#define IWLAGN_NUM_QUEUES		20

#endif /* __iwl_agn_hw_h__ */
