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
#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/sched.h>
#include <asm/openprom.h>
#include <asm/oplib.h>
#include <beep/string.h>

extern void restore_current(void);

/* Non blocking put character to console device, returns -1 if
 * unsuccessful.
 */
static int prom_nbputchar(const char *buf)
{
	unsigned long flags;
	int i = -1;

	spin_lock_irqsave(&prom_lock, flags);
	switch(prom_vers) {
	case PROM_V0:
		if ((*(romvec->pv_nbputchar))(*buf))
			i = 1;
		break;
	case PROM_V2:
	case PROM_V3:
		if ((*(romvec->pv_v2devops).v2_dev_write)(*romvec->pv_v2bootargs.fd_stdout,
							  buf, 0x1) == 1)
			i = 1;
		break;
	default:
		break;
	}
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
	return i; /* Ugh, we could spin forever on unsupported proms ;( */
}

void prom_console_write_buf(const char *buf, int len)
{
	while (len) {
		int n = prom_nbputchar(buf);
		if (n < 0)
			continue;
		len--;
		buf++;
	}
}

