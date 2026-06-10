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
#ifndef _ASM_X86_MACH_DEFAULT_APM_H
#define _ASM_X86_MACH_DEFAULT_APM_H

#ifdef APM_ZERO_SEGS
#	define APM_DO_ZERO_SEGS \
		"pushl %%ds\n\t" \
		"pushl %%es\n\t" \
		"xorl %%edx, %%edx\n\t" \
		"mov %%dx, %%ds\n\t" \
		"mov %%dx, %%es\n\t" \
		"mov %%dx, %%fs\n\t" \
		"mov %%dx, %%gs\n\t"
#	define APM_DO_POP_SEGS \
		"popl %%es\n\t" \
		"popl %%ds\n\t"
#else
#	define APM_DO_ZERO_SEGS
#	define APM_DO_POP_SEGS
#endif

static inline void apm_bios_call_asm(u32 func, u32 ebx_in, u32 ecx_in,
					u32 *eax, u32 *ebx, u32 *ecx,
					u32 *edx, u32 *esi)
{
	/*
	 * N.B. We do NOT need a cld after the BIOS call
	 * because we always save and restore the flags.
	 */
	__asm__ __volatile__(APM_DO_ZERO_SEGS
		"pushl %%edi\n\t"
		"pushl %%ebp\n\t"
		"lcall *%%cs:apm_bios_entry\n\t"
		"setc %%al\n\t"
		"popl %%ebp\n\t"
		"popl %%edi\n\t"
		APM_DO_POP_SEGS
		: "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx),
		  "=S" (*esi)
		: "a" (func), "b" (ebx_in), "c" (ecx_in)
		: "memory", "cc");
}

static inline u8 apm_bios_call_simple_asm(u32 func, u32 ebx_in,
						u32 ecx_in, u32 *eax)
{
	int	cx, dx, si;
	u8	error;

	/*
	 * N.B. We do NOT need a cld after the BIOS call
	 * because we always save and restore the flags.
	 */
	__asm__ __volatile__(APM_DO_ZERO_SEGS
		"pushl %%edi\n\t"
		"pushl %%ebp\n\t"
		"lcall *%%cs:apm_bios_entry\n\t"
		"setc %%bl\n\t"
		"popl %%ebp\n\t"
		"popl %%edi\n\t"
		APM_DO_POP_SEGS
		: "=a" (*eax), "=b" (error), "=c" (cx), "=d" (dx),
		  "=S" (si)
		: "a" (func), "b" (ebx_in), "c" (ecx_in)
		: "memory", "cc");
	return error;
}

#endif /* _ASM_X86_MACH_DEFAULT_APM_H */
