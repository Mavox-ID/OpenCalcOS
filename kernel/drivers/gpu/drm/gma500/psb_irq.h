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
#ifndef _SYSIRQ_H_
#define _SYSIRQ_H_

#include <drm/drmP.h>

bool sysirq_init(struct drm_device *dev);
void sysirq_uninit(struct drm_device *dev);

void psb_irq_preinstall(struct drm_device *dev);
int  psb_irq_postinstall(struct drm_device *dev);
void psb_irq_uninstall(struct drm_device *dev);
irqreturn_t psb_irq_handler(DRM_IRQ_ARGS);

int psb_irq_enable_dpst(struct drm_device *dev);
int psb_irq_disable_dpst(struct drm_device *dev);
void psb_irq_turn_on_dpst(struct drm_device *dev);
void psb_irq_turn_off_dpst(struct drm_device *dev);
int  psb_enable_vblank(struct drm_device *dev, int pipe);
void psb_disable_vblank(struct drm_device *dev, int pipe);
u32  psb_get_vblank_counter(struct drm_device *dev, int pipe);

int mdfld_enable_te(struct drm_device *dev, int pipe);
void mdfld_disable_te(struct drm_device *dev, int pipe);
#endif /* _SYSIRQ_H_ */
