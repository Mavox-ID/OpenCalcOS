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
#ifndef _ASM_X86_XEN_HYPERVISOR_H
#define _ASM_X86_XEN_HYPERVISOR_H

extern struct shared_info *HYPERVISOR_shared_info;
extern struct start_info *xen_start_info;

#include <asm/processor.h>

static inline uint32_t xen_cpuid_base(void)
{
	uint32_t base, eax, ebx, ecx, edx;
	char signature[13];

	for (base = 0x40000000; base < 0x40010000; base += 0x100) {
		cpuid(base, &eax, &ebx, &ecx, &edx);
		*(uint32_t *)(signature + 0) = ebx;
		*(uint32_t *)(signature + 4) = ecx;
		*(uint32_t *)(signature + 8) = edx;
		signature[12] = 0;

		if (!strcmp("XenVMMXenVMM", signature) && ((eax - base) >= 2))
			return base;
	}

	return 0;
}

#ifdef CONFIG_XEN
extern bool xen_hvm_need_lapic(void);

static inline bool xen_x2apic_para_available(void)
{
	return xen_hvm_need_lapic();
}
#else
static inline bool xen_x2apic_para_available(void)
{
	return (xen_cpuid_base() != 0);
}
#endif

#endif /* _ASM_X86_XEN_HYPERVISOR_H */
