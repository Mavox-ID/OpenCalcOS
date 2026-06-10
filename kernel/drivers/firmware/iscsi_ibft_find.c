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
#include <beep/bootmem.h>
#include <beep/blkdev.h>
#include <beep/ctype.h>
#include <beep/device.h>
#include <beep/efi.h>
#include <beep/err.h>
#include <beep/init.h>
#include <beep/limits.h>
#include <beep/module.h>
#include <beep/pci.h>
#include <beep/stat.h>
#include <beep/string.h>
#include <beep/types.h>
#include <beep/acpi.h>
#include <beep/iscsi_ibft.h>

#include <asm/mmzone.h>

/*
 * Physical location of iSCSI Boot Format Table.
 */
struct acpi_table_ibft *ibft_addr;
EXPORT_SYMBOL_GPL(ibft_addr);

static const struct {
	char *sign;
} ibft_signs[] = {
	{ "iBFT" },
	{ "BIFT" },	/* Broadcom iSCSI Offload */
};

#define IBFT_SIGN_LEN 4
#define IBFT_START 0x80000 /* 512kB */
#define IBFT_END 0x100000 /* 1MB */
#define VGA_MEM 0xA0000 /* VGA buffer */
#define VGA_SIZE 0x20000 /* 128kB */

static int __init find_ibft_in_mem(void)
{
	unsigned long pos;
	unsigned int len = 0;
	void *virt;
	int i;

	for (pos = IBFT_START; pos < IBFT_END; pos += 16) {
		/* The table can't be inside the VGA BIOS reserved space,
		 * so skip that area */
		if (pos == VGA_MEM)
			pos += VGA_SIZE;
		virt = isa_bus_to_virt(pos);

		for (i = 0; i < ARRAY_SIZE(ibft_signs); i++) {
			if (memcmp(virt, ibft_signs[i].sign, IBFT_SIGN_LEN) ==
			    0) {
				unsigned long *addr =
				    (unsigned long *)isa_bus_to_virt(pos + 4);
				len = *addr;
				/* if the length of the table extends past 1M,
				 * the table cannot be valid. */
				if (pos + len <= (IBFT_END-1)) {
					ibft_addr = (struct acpi_table_ibft *)virt;
					pr_info("iBFT found at 0x%lx.\n", pos);
					goto done;
				}
			}
		}
	}
done:
	return len;
}
/*
 * Routine used to find the iSCSI Boot Format Table. The logical
 * kernel address is set in the ibft_addr global variable.
 */
unsigned long __init find_ibft_region(unsigned long *sizep)
{
	ibft_addr = NULL;

	/* iBFT 1.03 section 1.4.3.1 mandates that UEFI machines will
	 * only use ACPI for this */

	if (!efi_enabled)
		find_ibft_in_mem();

	if (ibft_addr) {
		*sizep = PAGE_ALIGN(ibft_addr->header.length);
		return (u64)isa_virt_to_bus(ibft_addr);
	}

	*sizep = 0;
	return 0;
}
