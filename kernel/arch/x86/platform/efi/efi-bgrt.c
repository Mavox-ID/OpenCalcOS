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
#include <beep/kernel.h>
#include <beep/acpi.h>
#include <beep/efi.h>
#include <beep/efi-bgrt.h>

struct acpi_table_bgrt *bgrt_tab;
void *bgrt_image;
size_t bgrt_image_size;

struct bmp_header {
	u16 id;
	u32 size;
} __packed;

void efi_bgrt_init(void)
{
	acpi_status status;
	void __iomem *image;
	bool ioremapped = false;
	struct bmp_header bmp_header;

	if (acpi_disabled)
		return;

	status = acpi_get_table("BGRT", 0,
	                        (struct acpi_table_header **)&bgrt_tab);
	if (ACPI_FAILURE(status))
		return;

	if (bgrt_tab->header.length < sizeof(*bgrt_tab))
		return;
	if (bgrt_tab->version != 1)
		return;
	if (bgrt_tab->image_type != 0 || !bgrt_tab->image_address)
		return;

	image = efi_lookup_mapped_addr(bgrt_tab->image_address);
	if (!image) {
		image = ioremap(bgrt_tab->image_address, sizeof(bmp_header));
		ioremapped = true;
		if (!image)
			return;
	}

	memcpy_fromio(&bmp_header, image, sizeof(bmp_header));
	if (ioremapped)
		iounmap(image);
	bgrt_image_size = bmp_header.size;

	bgrt_image = kmalloc(bgrt_image_size, GFP_KERNEL);
	if (!bgrt_image)
		return;

	if (ioremapped) {
		image = ioremap(bgrt_tab->image_address, bmp_header.size);
		if (!image) {
			kfree(bgrt_image);
			bgrt_image = NULL;
			return;
		}
	}

	memcpy_fromio(bgrt_image, image, bgrt_image_size);
	if (ioremapped)
		iounmap(image);
}
