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
#include <beep/console.h>
#include <beep/init.h>
#include <beep/kdev_t.h>
#include <beep/kernel.h>
#include <beep/major.h>
#include <beep/param.h>
#include <beep/root_dev.h>
#include <beep/string.h>
#include <beep/types.h>

#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/pal.h>
#include <asm/machvec.h>
#include <asm/pgtable.h>
#include <asm/sal.h>
#include <asm/hpsim.h>

#include "hpsim_ssc.h"

void
ia64_ctl_trace (long on)
{
	ia64_ssc(on, 0, 0, 0, SSC_CTL_TRACE);
}

void __init
hpsim_setup (char **cmdline_p)
{
	ROOT_DEV = Root_SDA1;		/* default to first SCSI drive */

	simcons_register();
}
