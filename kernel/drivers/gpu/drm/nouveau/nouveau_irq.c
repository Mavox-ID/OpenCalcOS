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
#include <subdev/mc.h>

#include "nouveau_drm.h"
#include "nouveau_irq.h"
#include "nv50_display.h"

void
nouveau_irq_preinstall(struct drm_device *dev)
{
	nv_wr32(nouveau_dev(dev), 0x000140, 0x00000000);
}

int
nouveau_irq_postinstall(struct drm_device *dev)
{
	nv_wr32(nouveau_dev(dev), 0x000140, 0x00000001);
	return 0;
}

void
nouveau_irq_uninstall(struct drm_device *dev)
{
	nv_wr32(nouveau_dev(dev), 0x000140, 0x00000000);
}

irqreturn_t
nouveau_irq_handler(DRM_IRQ_ARGS)
{
	struct drm_device *dev = arg;
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_mc *pmc = nouveau_mc(device);
	u32 stat;

	stat = nv_rd32(device, 0x000100);
	if (stat == 0 || stat == ~0)
		return IRQ_NONE;

	nv_subdev(pmc)->intr(nv_subdev(pmc));
	return IRQ_HANDLED;
}

int
nouveau_irq_init(struct drm_device *dev)
{
	return drm_irq_install(dev);
}

void
nouveau_irq_fini(struct drm_device *dev)
{
	drm_irq_uninstall(dev);
}
