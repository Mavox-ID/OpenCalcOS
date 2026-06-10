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
#ifndef _ASM_X86_UV_UV_IRQ_H
#define _ASM_X86_UV_UV_IRQ_H

/* If a generic version of this structure gets defined, eliminate this one. */
struct uv_IO_APIC_route_entry {
	__u64	vector		:  8,
		delivery_mode	:  3,
		dest_mode	:  1,
		delivery_status	:  1,
		polarity	:  1,
		__reserved_1	:  1,
		trigger		:  1,
		mask		:  1,
		__reserved_2	: 15,
		dest		: 32;
};

enum {
	UV_AFFINITY_ALL,
	UV_AFFINITY_NODE,
	UV_AFFINITY_CPU
};

extern int uv_irq_2_mmr_info(int, unsigned long *, int *);
extern int uv_setup_irq(char *, int, int, unsigned long, int);
extern void uv_teardown_irq(unsigned int);

#endif /* _ASM_X86_UV_UV_IRQ_H */
