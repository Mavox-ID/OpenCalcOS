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
#ifndef __ASMARM_CACHE_H
#define __ASMARM_CACHE_H

#define L1_CACHE_SHIFT		CONFIG_ARM_L1_CACHE_SHIFT
#define L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)

/*
 * Memory returned by kmalloc() may be used for DMA, so we must make
 * sure that all such allocations are cache aligned. Otherwise,
 * unrelated code may cause parts of the buffer to be read into the
 * cache before the transfer is done, causing old data to be seen by
 * the CPU.
 */
#define ARCH_DMA_MINALIGN	L1_CACHE_BYTES

/*
 * With EABI on ARMv5 and above we must have 64-bit aligned slab pointers.
 */
#if defined(CONFIG_AEABI) && (__BEEP_ARM_ARCH__ >= 5)
#define ARCH_SLAB_MINALIGN 8
#endif

#define __read_mostly __attribute__((__section__(".data..read_mostly")))

#endif
