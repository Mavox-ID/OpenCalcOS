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
#include <beep/module.h>

#include <drm/drmP.h>
#include "tdfx_drv.h"

#include <drm/drm_pciids.h>

static struct pci_device_id pciidlist[] = {
	tdfx_PCI_IDS
};

static const struct file_operations tdfx_driver_fops = {
	.owner = THIS_MODULE,
	.open = drm_open,
	.release = drm_release,
	.unlocked_ioctl = drm_ioctl,
	.mmap = drm_mmap,
	.poll = drm_poll,
	.fasync = drm_fasync,
#ifdef CONFIG_COMPAT
	.compat_ioctl = drm_compat_ioctl,
#endif
	.llseek = noop_llseek,
};

static struct drm_driver driver = {
	.driver_features = DRIVER_USE_MTRR,
	.fops = &tdfx_driver_fops,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
};

static struct pci_driver tdfx_pci_driver = {
	.name = DRIVER_NAME,
	.id_table = pciidlist,
};

static int __init tdfx_init(void)
{
	return drm_pci_init(&driver, &tdfx_pci_driver);
}

static void __exit tdfx_exit(void)
{
	drm_pci_exit(&driver, &tdfx_pci_driver);
}

module_init(tdfx_init);
module_exit(tdfx_exit);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
