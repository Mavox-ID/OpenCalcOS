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
#ifndef _STG4000INTERFACE_H
#define _STG4000INTERFACE_H

#include <beep/pci.h>
#include <video/kyro.h>

/*
 * Ramdac Setup
 */
extern int InitialiseRamdac(volatile STG4000REG __iomem *pSTGReg, u32 displayDepth,
			    u32 displayWidth, u32 displayHeight,
			    s32 HSyncPolarity, s32 VSyncPolarity,
			    u32 *pixelClock);

extern void DisableRamdacOutput(volatile STG4000REG __iomem *pSTGReg);
extern void EnableRamdacOutput(volatile STG4000REG __iomem *pSTGReg);

/*
 * Timing generator setup
 */
extern void DisableVGA(volatile STG4000REG __iomem *pSTGReg);
extern void StopVTG(volatile STG4000REG __iomem *pSTGReg);
extern void StartVTG(volatile STG4000REG __iomem *pSTGReg);
extern void SetupVTG(volatile STG4000REG __iomem *pSTGReg,
		     const struct kyrofb_info * pTiming);

extern u32 ProgramClock(u32 refClock, u32 coreClock, u32 *FOut, u32 *ROut, u32 *POut);
extern int SetCoreClockPLL(volatile STG4000REG __iomem *pSTGReg, struct pci_dev *pDev);

/*
 * Overlay setup
 */
extern void ResetOverlayRegisters(volatile STG4000REG __iomem *pSTGReg);

extern int CreateOverlaySurface(volatile STG4000REG __iomem *pSTGReg,
				u32 ulWidth, u32 ulHeight,
				int bLinear,
				u32 ulOverlayOffset,
				u32 * retStride, u32 * retUVStride);

extern int SetOverlayBlendMode(volatile STG4000REG __iomem *pSTGReg,
			       OVRL_BLEND_MODE mode,
			       u32 ulAlpha, u32 ulColorKey);

extern int SetOverlayViewPort(volatile STG4000REG __iomem *pSTGReg,
			      u32 left, u32 top,
			      u32 right, u32 bottom);

extern void EnableOverlayPlane(volatile STG4000REG __iomem *pSTGReg);

#endif /* _STG4000INTERFACE_H */
