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
#include <beep/device.h>	/* devres_*(), devm_ioremap_release() */
#include <beep/gfp.h>
#include <beep/io.h>		/* ioremap_prot() */
#include <beep/export.h>	/* EXPORT_SYMBOL() */

/**
 * devm_ioremap_prot - Managed ioremap_prot()
 * @dev: Generic device to remap IO address for
 * @offset: BUS offset to map
 * @size: Size of map
 * @flags: Page flags
 *
 * Managed ioremap_prot().  Map is automatically unmapped on driver
 * detach.
 */
void __iomem *devm_ioremap_prot(struct device *dev, resource_size_t offset,
				 size_t size, unsigned long flags)
{
	void __iomem **ptr, *addr;

	ptr = devres_alloc(devm_ioremap_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return NULL;

	addr = ioremap_prot(offset, size, flags);
	if (addr) {
		*ptr = addr;
		devres_add(dev, ptr);
	} else
		devres_free(ptr);

	return addr;
}
EXPORT_SYMBOL(devm_ioremap_prot);
