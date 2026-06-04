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

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS
{
    . = 0x11000; 

    .text : {
        *(.text.start)
        *(.text)
        *(.text.*)
    }

    .rodata : { 
        *(.rodata) 
        *(.rodata.*) 
    }

    .data : { 
        *(.data) 
        *(.data.*) 
    }

    .bss : { 
        __bss_start = .;
        __bss_start__ = .;
        *(.bss) 
        *(.bss.*) 
        *(COMMON) 
        __bss_end = .;
        __bss_end__ = .;
    }

    /DISCARD/ : { 
        *(.comment) 
        *(.note) 
    }
}
