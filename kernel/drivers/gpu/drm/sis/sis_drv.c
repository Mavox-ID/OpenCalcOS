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
#include <drm/sis_drm.h>
#include "sis_drv.h"

#include <drm/drm_pciids.h>

static struct pci_device_id pciidlist[] = {
	sisdrv_PCI_IDS
};

static int sis_driver_load(struct drm_device *dev, unsigned long chipset)
{
	drm_sis_private_t *dev_priv;

	pci_set_master(dev->pdev);

	dev_priv = kzalloc(sizeof(drm_sis_private_t), GFP_KERNEL);
	if (dev_priv == NULL)
		return -ENOMEM;

	idr_init(&dev_priv->object_idr);
	dev->dev_private = (void *)dev_priv;
	dev_priv->chipset = chipset;

	return 0;
}

static int sis_driver_unload(struct drm_device *dev)
{
	drm_sis_private_t *dev_priv = dev->dev_private;

	idr_remove_all(&dev_priv->object_idr);
	idr_destroy(&dev_priv->object_idr);

	kfree(dev_priv);

	return 0;
}

static const struct file_operations sis_driver_fops = {
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

static int sis_driver_open(struct drm_device *dev, struct drm_file *file)
{
	struct sis_file_private *file_priv;

	DRM_DEBUG_DRIVER("\n");
	file_priv = kmalloc(sizeof(*file_priv), GFP_KERNEL);
	if (!file_priv)
		return -ENOMEM;

	file->driver_priv = file_priv;

	INIT_LIST_HEAD(&file_priv->obj_list);

	return 0;
}

void sis_driver_postclose(struct drm_device *dev, struct drm_file *file)
{
	struct sis_file_private *file_priv = file->driver_priv;

	kfree(file_priv);
}

static struct drm_driver driver = {
	.driver_features = DRIVER_USE_AGP | DRIVER_USE_MTRR,
	.load = sis_driver_load,
	.unload = sis_driver_unload,
	.open = sis_driver_open,
	.preclose = sis_reclaim_buffers_locked,
	.postclose = sis_driver_postclose,
	.dma_quiescent = sis_idle,
	.lastclose = sis_lastclose,
	.ioctls = sis_ioctls,
	.fops = &sis_driver_fops,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
};

static struct pci_driver sis_pci_driver = {
	.name = DRIVER_NAME,
	.id_table = pciidlist,
};

static int __init sis_init(void)
{
	driver.num_ioctls = sis_max_ioctl;
	return drm_pci_init(&driver, &sis_pci_driver);
}

static void __exit sis_exit(void)
{
	drm_pci_exit(&driver, &sis_pci_driver);
}

module_init(sis_init);
module_exit(sis_exit);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
