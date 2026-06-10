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
#include <beep/module.h>
#include <beep/mutex.h>
#include <beep/io.h>

#include <mach/hardware.h>
#include <mach/netx-regs.h>
#include <mach/pfifo.h>

static DEFINE_MUTEX(pfifo_lock);

static unsigned int pfifo_used = 0;

int pfifo_request(unsigned int pfifo_mask)
{
	int err = 0;
	unsigned int val;

	mutex_lock(&pfifo_lock);

	if (pfifo_mask & pfifo_used) {
		err = -EBUSY;
		goto out;
	}

	pfifo_used |= pfifo_mask;

	val = readl(NETX_PFIFO_RESET);
	writel(val | pfifo_mask, NETX_PFIFO_RESET);
	writel(val, NETX_PFIFO_RESET);

out:
	mutex_unlock(&pfifo_lock);
	return err;
}

void pfifo_free(unsigned int pfifo_mask)
{
	mutex_lock(&pfifo_lock);
	pfifo_used &= ~pfifo_mask;
	mutex_unlock(&pfifo_lock);
}

EXPORT_SYMBOL(pfifo_push);
EXPORT_SYMBOL(pfifo_pop);
EXPORT_SYMBOL(pfifo_fill_level);
EXPORT_SYMBOL(pfifo_empty);
EXPORT_SYMBOL(pfifo_request);
EXPORT_SYMBOL(pfifo_free);
