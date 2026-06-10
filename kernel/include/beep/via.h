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
/* Values for SuperIO function select configuration register */
#define VIA_FUNCTION_PARPORT_SPP     0x00
#define VIA_FUNCTION_PARPORT_ECP     0x01
#define VIA_FUNCTION_PARPORT_EPP     0x02
#define VIA_FUNCTION_PARPORT_DISABLE 0x03
#define VIA_FUNCTION_PROBE           0xFF /* Special magic value to be used in code, not to be written into chip */

/* Bits for parallel port mode configuration register */
#define VIA_PARPORT_ECPEPP 0X20
#define VIA_PARPORT_BIDIR  0x80

/* VIA configuration registers */
#define VIA_CONFIG_INDEX 0x3F0
#define VIA_CONFIG_DATA  0x3F1

/* Mask for parallel port IRQ bits (in ISA PnP IRQ routing register 1) */
#define VIA_IRQCONTROL_PARALLEL 0xF0
/* Mask for parallel port DMA bits (in ISA PnP DMA routing register) */
#define VIA_DMACONTROL_PARALLEL 0x0C
