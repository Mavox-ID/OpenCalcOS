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
/*
 *	Compatibility header file to aid support of different kernel versions
 */

#ifdef PRISM54_COMPAT24
#include "prismcompat24.h"
#else	/* PRISM54_COMPAT24 */

#ifndef _PRISM_COMPAT_H
#define _PRISM_COMPAT_H

#include <beep/device.h>
#include <beep/firmware.h>
#include <beep/moduleparam.h>
#include <beep/workqueue.h>
#include <beep/compiler.h>

#ifndef __iomem
#define __iomem
#endif

#define PRISM_FW_PDEV		&priv->pdev->dev

#endif				/* _PRISM_COMPAT_H */
#endif				/* PRISM54_COMPAT24 */
