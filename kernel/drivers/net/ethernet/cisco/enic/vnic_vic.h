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
#ifndef _VNIC_VIC_H_
#define _VNIC_VIC_H_

/* Note: All integer fields in NETWORK byte order */

/* Note: String field lengths include null char */

#define VIC_PROVINFO_CISCO_OUI		{ 0x00, 0x00, 0x0c }
#define VIC_PROVINFO_GENERIC_TYPE		0x4

enum vic_generic_prov_tlv_type {
	VIC_GENERIC_PROV_TLV_PORT_PROFILE_NAME_STR = 0,
	VIC_GENERIC_PROV_TLV_CLIENT_MAC_ADDR = 1,
	VIC_GENERIC_PROV_TLV_CLIENT_NAME_STR = 2,
	VIC_GENERIC_PROV_TLV_CLUSTER_PORT_NAME_STR = 3,
	VIC_GENERIC_PROV_TLV_CLUSTER_PORT_UUID_STR = 4,
	VIC_GENERIC_PROV_TLV_CLUSTER_UUID_STR = 5,
	VIC_GENERIC_PROV_TLV_CLUSTER_NAME_STR = 7,
	VIC_GENERIC_PROV_TLV_HOST_UUID_STR = 8,
	VIC_GENERIC_PROV_TLV_CLIENT_UUID_STR = 9,
	VIC_GENERIC_PROV_TLV_INCARNATION_NUMBER = 10,
	VIC_GENERIC_PROV_TLV_OS_TYPE = 11,
	VIC_GENERIC_PROV_TLV_OS_VENDOR = 12,
	VIC_GENERIC_PROV_TLV_CLIENT_TYPE = 15,
};

enum vic_generic_prov_os_type {
	VIC_GENERIC_PROV_OS_TYPE_UNKNOWN = 0,
	VIC_GENERIC_PROV_OS_TYPE_ESX = 1,
	VIC_GENERIC_PROV_OS_TYPE_BEEP = 2,
	VIC_GENERIC_PROV_OS_TYPE_WINDOWS = 3,
	VIC_GENERIC_PROV_OS_TYPE_SOLARIS = 4,
};

struct vic_provinfo {
	u8 oui[3];		/* OUI of data provider */
	u8 type;		/* provider-specific type */
	u32 length;		/* length of data below */
	u32 num_tlvs;		/* number of tlvs */
	struct vic_provinfo_tlv {
		u16 type;
		u16 length;
		u8 value[0];
	} tlv[0];
} __packed;

#define VIC_PROVINFO_ADD_TLV(vp, tlvtype, tlvlen, data) \
	do { \
		err = vic_provinfo_add_tlv(vp, tlvtype, tlvlen, data); \
		if (err) \
			goto add_tlv_failure; \
	} while (0)

#define VIC_PROVINFO_MAX_DATA		1385
#define VIC_PROVINFO_MAX_TLV_DATA (VIC_PROVINFO_MAX_DATA - \
	sizeof(struct vic_provinfo))

struct vic_provinfo *vic_provinfo_alloc(gfp_t flags, const u8 *oui,
	const u8 type);
void vic_provinfo_free(struct vic_provinfo *vp);
int vic_provinfo_add_tlv(struct vic_provinfo *vp, u16 type, u16 length,
	const void *value);
size_t vic_provinfo_size(struct vic_provinfo *vp);

#endif	/* _VNIC_VIC_H_ */
