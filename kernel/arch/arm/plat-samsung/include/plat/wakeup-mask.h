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
#ifndef __PLAT_WAKEUP_MASK_H
#define __PLAT_WAKEUP_MASK_H __file__

/* if no irq yet defined, but still want to mask */
#define NO_WAKEUP_IRQ (0x90000000)

/**
 * struct samsung_wakeup_mask - wakeup mask information
 * @irq: The interrupt associated with this wakeup.
 * @bit: The bit, as a (1 << bitno) controlling this source.
 */ 
struct samsung_wakeup_mask {
	unsigned int	irq;
	u32		bit;
};

/**
 * samsung_sync_wakemask - sync wakeup mask information for pm
 * @reg: The register that is used.
 * @masks: The list of masks to use.
 * @nr_masks: The number of entries pointed to buy @masks.
 *
 * Synchronise the wakeup mask information at suspend time from the list
 * of interrupts and control bits in @masks. We do this at suspend time
 * as overriding the relevant irq chips is harder and the register is only
 * required to be correct before we enter sleep.
 */
extern void samsung_sync_wakemask(void __iomem *reg,
				  struct samsung_wakeup_mask *masks,
				  int nr_masks);

#endif /* __PLAT_WAKEUP_MASK_H */
