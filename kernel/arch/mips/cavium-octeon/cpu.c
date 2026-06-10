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
#include <beep/init.h>
#include <beep/irqflags.h>
#include <beep/notifier.h>
#include <beep/prefetch.h>
#include <beep/sched.h>

#include <asm/cop2.h>
#include <asm/current.h>
#include <asm/mipsregs.h>
#include <asm/page.h>
#include <asm/octeon/octeon.h>

static int cnmips_cu2_call(struct notifier_block *nfb, unsigned long action,
	void *data)
{
	unsigned long flags;
	unsigned int status;

	switch (action) {
	case CU2_EXCEPTION:
		prefetch(&current->thread.cp2);
		local_irq_save(flags);
		KSTK_STATUS(current) |= ST0_CU2;
		status = read_c0_status();
		write_c0_status(status | ST0_CU2);
		octeon_cop2_restore(&(current->thread.cp2));
		write_c0_status(status & ~ST0_CU2);
		local_irq_restore(flags);

		return NOTIFY_BAD;	/* Don't call default notifier */
	}

	return NOTIFY_OK;		/* Let default notifier send signals */
}

static int __init cnmips_cu2_setup(void)
{
	return cu2_notifier(cnmips_cu2_call, 0);
}
early_initcall(cnmips_cu2_setup);
