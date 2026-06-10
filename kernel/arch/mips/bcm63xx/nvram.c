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
#define pr_fmt(fmt) "bcm63xx_nvram: " fmt

#include <beep/init.h>
#include <beep/crc32.h>
#include <beep/export.h>
#include <beep/kernel.h>
#include <beep/if_ether.h>

#include <bcm63xx_nvram.h>

/*
 * nvram structure
 */
struct bcm963xx_nvram {
	u32	version;
	u8	reserved1[256];
	u8	name[16];
	u32	main_tp_number;
	u32	psi_size;
	u32	mac_addr_count;
	u8	mac_addr_base[ETH_ALEN];
	u8	reserved2[2];
	u32	checksum_old;
	u8	reserved3[720];
	u32	checksum_high;
};

static struct bcm963xx_nvram nvram;
static int mac_addr_used;

int __init bcm63xx_nvram_init(void *addr)
{
	unsigned int check_len;
	u32 crc, expected_crc;

	/* extract nvram data */
	memcpy(&nvram, addr, sizeof(nvram));

	/* check checksum before using data */
	if (nvram.version <= 4) {
		check_len = offsetof(struct bcm963xx_nvram, reserved3);
		expected_crc = nvram.checksum_old;
		nvram.checksum_old = 0;
	} else {
		check_len = sizeof(nvram);
		expected_crc = nvram.checksum_high;
		nvram.checksum_high = 0;
	}

	crc = crc32_le(~0, (u8 *)&nvram, check_len);

	if (crc != expected_crc)
		return -EINVAL;

	return 0;
}

u8 *bcm63xx_nvram_get_name(void)
{
	return nvram.name;
}
EXPORT_SYMBOL(bcm63xx_nvram_get_name);

int bcm63xx_nvram_get_mac_address(u8 *mac)
{
	u8 *oui;
	int count;

	if (mac_addr_used >= nvram.mac_addr_count) {
		pr_err("not enough mac addresses\n");
		return -ENODEV;
	}

	memcpy(mac, nvram.mac_addr_base, ETH_ALEN);
	oui = mac + ETH_ALEN/2 - 1;
	count = mac_addr_used;

	while (count--) {
		u8 *p = mac + ETH_ALEN - 1;

		do {
			(*p)++;
			if (*p != 0)
				break;
			p--;
		} while (p != oui);

		if (p == oui) {
			pr_err("unable to fetch mac address\n");
			return -ENODEV;
		}
	}

	mac_addr_used++;
	return 0;
}
EXPORT_SYMBOL(bcm63xx_nvram_get_mac_address);
