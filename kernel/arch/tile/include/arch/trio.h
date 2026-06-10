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
/* Machine-generated file; do not edit. */

#ifndef __ARCH_TRIO_H__
#define __ARCH_TRIO_H__

#include <arch/abi.h>
#include <arch/trio_def.h>

#ifndef __ASSEMBLER__

/*
 * Tile PIO Region Configuration - CFG Address Format.
 * This register describes the address format for PIO accesses when the
 * associated region is setup with TYPE=CFG.
 */

__extension__
typedef union
{
  struct
  {
#ifndef __BIG_ENDIAN__
    /* Register Address (full byte address). */
    uint_reg_t reg_addr     : 12;
    /* Function Number */
    uint_reg_t fn           : 3;
    /* Device Number */
    uint_reg_t dev          : 5;
    /* BUS Number */
    uint_reg_t bus          : 8;
    /* Config Type: 0 for access to directly-attached device.  1 otherwise. */
    uint_reg_t type         : 1;
    /* Reserved. */
    uint_reg_t __reserved_0 : 1;
    /*
     * MAC select.  This must match the configuration in
     * TILE_PIO_REGION_SETUP.MAC.
     */
    uint_reg_t mac          : 2;
    /* Reserved. */
    uint_reg_t __reserved_1 : 32;
#else   /* __BIG_ENDIAN__ */
    uint_reg_t __reserved_1 : 32;
    uint_reg_t mac          : 2;
    uint_reg_t __reserved_0 : 1;
    uint_reg_t type         : 1;
    uint_reg_t bus          : 8;
    uint_reg_t dev          : 5;
    uint_reg_t fn           : 3;
    uint_reg_t reg_addr     : 12;
#endif
  };

  uint_reg_t word;
} TRIO_TILE_PIO_REGION_SETUP_CFG_ADDR_t;
#endif /* !defined(__ASSEMBLER__) */

#endif /* !defined(__ARCH_TRIO_H__) */
