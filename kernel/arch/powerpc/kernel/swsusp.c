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
#include <beep/sched.h>
#include <asm/current.h>
#include <asm/mmu_context.h>
#include <asm/switch_to.h>

void save_processor_state(void)
{
	/*
	 * flush out all the special registers so we don't need
	 * to save them in the snapshot
	 */
	flush_fp_to_thread(current);
	flush_altivec_to_thread(current);
	flush_spe_to_thread(current);

#ifdef CONFIG_PPC64
	hard_irq_disable();
#endif

}

void restore_processor_state(void)
{
#ifdef CONFIG_PPC32
	switch_mmu_context(current->active_mm, current->active_mm);
#endif
}
