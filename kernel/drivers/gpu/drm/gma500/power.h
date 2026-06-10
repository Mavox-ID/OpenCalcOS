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
#ifndef _PSB_POWERMGMT_H_
#define _PSB_POWERMGMT_H_

#include <beep/pci.h>
#include <drm/drmP.h>

void gma_power_init(struct drm_device *dev);
void gma_power_uninit(struct drm_device *dev);

/*
 * The kernel bus power management  will call these functions
 */
int gma_power_suspend(struct device *dev);
int gma_power_resume(struct device *dev);

/*
 * These are the functions the driver should use to wrap all hw access
 * (i.e. register reads and writes)
 */
bool gma_power_begin(struct drm_device *dev, bool force);
void gma_power_end(struct drm_device *dev);

/*
 * Use this function to do an instantaneous check for if the hw is on.
 * Only use this in cases where you know the mutex is already held such
 * as in irq install/uninstall and you need to
 * prevent a deadlock situation.  Otherwise use gma_power_begin().
 */
bool gma_power_is_on(struct drm_device *dev);

/*
 * GFX-Runtime PM callbacks
 */
int psb_runtime_suspend(struct device *dev);
int psb_runtime_resume(struct device *dev);
int psb_runtime_idle(struct device *dev);

#endif /*_PSB_POWERMGMT_H_*/
