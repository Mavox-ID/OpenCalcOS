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
#ifndef __ASM_SH_CACHE_INSNS_64_H
#define __ASM_SH_CACHE_INSNS_64_H

#define __icbi(addr)	__asm__ __volatile__ ( "icbi %0, 0\n\t" : : "r" (addr))
#define __ocbp(addr)	__asm__ __volatile__ ( "ocbp %0, 0\n\t" : : "r" (addr))
#define __ocbi(addr)	__asm__ __volatile__ ( "ocbi %0, 0\n\t" : : "r" (addr))
#define __ocbwb(addr)	__asm__ __volatile__ ( "ocbwb %0, 0\n\t" : : "r" (addr))

static inline reg_size_t register_align(void *val)
{
	return (unsigned long long)(signed long long)(signed long)val;
}

#endif /* __ASM_SH_CACHE_INSNS_64_H */
