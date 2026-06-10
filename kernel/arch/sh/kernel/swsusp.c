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
#include <beep/mm.h>
#include <beep/sched.h>
#include <beep/suspend.h>
#include <asm/suspend.h>
#include <asm/sections.h>
#include <asm/tlbflush.h>
#include <asm/page.h>
#include <asm/fpu.h>

struct swsusp_arch_regs swsusp_arch_regs_cpu0;

int pfn_is_nosave(unsigned long pfn)
{
	unsigned long begin_pfn = __pa(&__nosave_begin) >> PAGE_SHIFT;
	unsigned long end_pfn = PAGE_ALIGN(__pa(&__nosave_end)) >> PAGE_SHIFT;

	return (pfn >= begin_pfn) && (pfn < end_pfn);
}

void save_processor_state(void)
{
	init_fpu(current);
}

void restore_processor_state(void)
{
	local_flush_tlb_all();
}
