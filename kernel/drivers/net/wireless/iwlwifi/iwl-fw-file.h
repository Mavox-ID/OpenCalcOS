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
#ifndef __iwl_fw_file_h__
#define __iwl_fw_file_h__

#include <beep/netdevice.h>

/* v1/v2 uCode file layout */
struct iwl_ucode_header {
	__le32 ver;	/* major/minor/API/serial */
	union {
		struct {
			__le32 inst_size;	/* bytes of runtime code */
			__le32 data_size;	/* bytes of runtime data */
			__le32 init_size;	/* bytes of init code */
			__le32 init_data_size;	/* bytes of init data */
			__le32 boot_size;	/* bytes of bootstrap code */
			u8 data[0];		/* in same order as sizes */
		} v1;
		struct {
			__le32 build;		/* build number */
			__le32 inst_size;	/* bytes of runtime code */
			__le32 data_size;	/* bytes of runtime data */
			__le32 init_size;	/* bytes of init code */
			__le32 init_data_size;	/* bytes of init data */
			__le32 boot_size;	/* bytes of bootstrap code */
			u8 data[0];		/* in same order as sizes */
		} v2;
	} u;
};

/*
 * new TLV uCode file layout
 *
 * The new TLV file format contains TLVs, that each specify
 * some piece of data.
 */

enum iwl_ucode_tlv_type {
	IWL_UCODE_TLV_INVALID		= 0, /* unused */
	IWL_UCODE_TLV_INST		= 1,
	IWL_UCODE_TLV_DATA		= 2,
	IWL_UCODE_TLV_INIT		= 3,
	IWL_UCODE_TLV_INIT_DATA		= 4,
	IWL_UCODE_TLV_BOOT		= 5,
	IWL_UCODE_TLV_PROBE_MAX_LEN	= 6, /* a u32 value */
	IWL_UCODE_TLV_PAN		= 7,
	IWL_UCODE_TLV_RUNT_EVTLOG_PTR	= 8,
	IWL_UCODE_TLV_RUNT_EVTLOG_SIZE	= 9,
	IWL_UCODE_TLV_RUNT_ERRLOG_PTR	= 10,
	IWL_UCODE_TLV_INIT_EVTLOG_PTR	= 11,
	IWL_UCODE_TLV_INIT_EVTLOG_SIZE	= 12,
	IWL_UCODE_TLV_INIT_ERRLOG_PTR	= 13,
	IWL_UCODE_TLV_ENHANCE_SENS_TBL	= 14,
	IWL_UCODE_TLV_PHY_CALIBRATION_SIZE = 15,
	IWL_UCODE_TLV_WOWLAN_INST	= 16,
	IWL_UCODE_TLV_WOWLAN_DATA	= 17,
	IWL_UCODE_TLV_FLAGS		= 18,
	IWL_UCODE_TLV_SEC_RT		= 19,
	IWL_UCODE_TLV_SEC_INIT		= 20,
	IWL_UCODE_TLV_SEC_WOWLAN	= 21,
	IWL_UCODE_TLV_DEF_CALIB		= 22,
	IWL_UCODE_TLV_PHY_SKU		= 23,
};

struct iwl_ucode_tlv {
	__le32 type;		/* see above */
	__le32 length;		/* not including type/length fields */
	u8 data[0];
};

#define IWL_TLV_UCODE_MAGIC	0x0a4c5749

struct iwl_tlv_ucode_header {
	/*
	 * The TLV style ucode header is distinguished from
	 * the v1/v2 style header by first four bytes being
	 * zero, as such is an invalid combination of
	 * major/minor/API/serial versions.
	 */
	__le32 zero;
	__le32 magic;
	u8 human_readable[64];
	__le32 ver;		/* major/minor/API/serial */
	__le32 build;
	__le64 ignore;
	/*
	 * The data contained herein has a TLV layout,
	 * see above for the TLV header and types.
	 * Note that each TLV is padded to a length
	 * that is a multiple of 4 for alignment.
	 */
	u8 data[0];
};

#endif  /* __iwl_fw_file_h__ */
