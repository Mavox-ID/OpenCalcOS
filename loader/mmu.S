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

.text
.align 4

.global mmu_trampoline
.global mmu_trampoline_end
.global flush_loader_caches

flush_loader_caches:
    mov r0, #0
1:  mrc p15, 0, r15, c7, c10, 3
    bne 1b
    mcr p15, 0, r0, c7, c10, 4
    mcr p15, 0, r0, c7, c5, 0
    bx lr

mmu_trampoline:
    mrc p15, 0, r3, c1, c0, 0
    bic r3, r3, #0x0005
    bic r3, r3, #0x1000
    mcr p15, 0, r3, c1, c0, 0
    
    nop
    nop
    nop

    mov r3, r0
    mov r0, #0
    bx r3

mmu_trampoline_end:
