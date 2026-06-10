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
#include <asm/suspend.h>
#include <asm/fpu.h>
#include <asm/dsp.h>

static u32 saved_status;
struct pt_regs saved_regs;

void save_processor_state(void)
{
	saved_status = read_c0_status();

	if (is_fpu_owner())
		save_fp(current);
	if (cpu_has_dsp)
		save_dsp(current);
}

void restore_processor_state(void)
{
	write_c0_status(saved_status);

	if (is_fpu_owner())
		restore_fp(current);
	if (cpu_has_dsp)
		restore_dsp(current);
}

int pfn_is_nosave(unsigned long pfn)
{
	unsigned long nosave_begin_pfn = PFN_DOWN(__pa(&__nosave_begin));
	unsigned long nosave_end_pfn = PFN_UP(__pa(&__nosave_end));

	return	(pfn >= nosave_begin_pfn) && (pfn < nosave_end_pfn);
}
