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
/**
 * @file drv_pcie_rc_intf.h
 * Interface definitions for the PCIE Root Complex.
 */

#ifndef _SYS_HV_DRV_PCIE_RC_INTF_H
#define _SYS_HV_DRV_PCIE_RC_INTF_H

/** File offset for reading the interrupt base number used for PCIE legacy
    interrupts and PLX Gen 1 requirement flag */
#define PCIE_RC_CONFIG_MASK_OFF 0


/**
 * Structure used for obtaining PCIe config information, read from the PCIE
 * subsystem /ctl file at initialization
 */
typedef struct pcie_rc_config
{
  int intr;                     /**< interrupt number used for downcall */
  int plx_gen1;                 /**< flag for PLX Gen 1 configuration */
} pcie_rc_config_t;

#endif  /* _SYS_HV_DRV_PCIE_RC_INTF_H */
