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
#ifndef DSPIOCTL_
#define DSPIOCTL_

/* ------------------------------------ Hardware Abstraction Layer */
#include <hw_defs.h>
#include <hw_mmu.h>

/*
 * Any IOCTLS at or above this value are reserved for standard Bridge driver
 * interfaces.
 */
#define BRDIOCTL_RESERVEDBASE       0x8000

#define BRDIOCTL_CHNLREAD           (BRDIOCTL_RESERVEDBASE + 0x10)
#define BRDIOCTL_CHNLWRITE          (BRDIOCTL_RESERVEDBASE + 0x20)
/* DMMU */
#define BRDIOCTL_SETMMUCONFIG       (BRDIOCTL_RESERVEDBASE + 0x60)
/* PWR */
#define BRDIOCTL_PWRCONTROL         (BRDIOCTL_RESERVEDBASE + 0x70)

/* attention, modifiers:
 * Some of these control enumerations are made visible to user for power
 * control, so any changes to this list, should also be updated in the user
 * header file 'dbdefs.h' ***/
/* These ioctls are reserved for PWR power commands for the DSP */
#define BRDIOCTL_DEEPSLEEP          (BRDIOCTL_PWRCONTROL + 0x0)
#define BRDIOCTL_EMERGENCYSLEEP     (BRDIOCTL_PWRCONTROL + 0x1)
#define BRDIOCTL_WAKEUP             (BRDIOCTL_PWRCONTROL + 0x2)
#define BRDIOCTL_CLK_CTRL		    (BRDIOCTL_PWRCONTROL + 0x7)
/* DSP Initiated Hibernate */
#define BRDIOCTL_PWR_HIBERNATE	(BRDIOCTL_PWRCONTROL + 0x8)
#define BRDIOCTL_PRESCALE_NOTIFY (BRDIOCTL_PWRCONTROL + 0x9)
#define BRDIOCTL_POSTSCALE_NOTIFY (BRDIOCTL_PWRCONTROL + 0xA)
#define BRDIOCTL_CONSTRAINT_REQUEST (BRDIOCTL_PWRCONTROL + 0xB)

/* Number of actual DSP-MMU TLB entries */
#define BRDIOCTL_NUMOFMMUTLB        32

struct bridge_ioctl_extproc {
	u32 dsp_va;		/* DSP virtual address */
	u32 gpp_pa;		/* GPP physical address */
	/* GPP virtual address. __va does not work for ioremapped addresses */
	u32 gpp_va;
	u32 size;		/* Size of the mapped memory in bytes */
	enum hw_endianism_t endianism;
	enum hw_mmu_mixed_size_t mixed_mode;
	enum hw_element_size_t elem_size;
};

#endif /* DSPIOCTL_ */
