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
#include <beep/kernel.h>
#include <beep/irqflags.h>

#include <asm/bcache.h>

#include <asm/fw/arc/types.h>
#include <asm/sgialib.h>
#include <asm/bootinfo.h>

VOID
ArcHalt(VOID)
{
	bc_disable();
	local_irq_disable();
	ARC_CALL0(halt);
never:	goto never;
}

VOID
ArcPowerDown(VOID)
{
	bc_disable();
	local_irq_disable();
	ARC_CALL0(pdown);
never:	goto never;
}

/* XXX is this a soft reset basically? XXX */
VOID
ArcRestart(VOID)
{
	bc_disable();
	local_irq_disable();
	ARC_CALL0(restart);
never:	goto never;
}

VOID
ArcReboot(VOID)
{
	bc_disable();
	local_irq_disable();
	ARC_CALL0(reboot);
never:	goto never;
}

VOID
ArcEnterInteractiveMode(VOID)
{
	bc_disable();
	local_irq_disable();
	ARC_CALL0(imode);
never:	goto never;
}

LONG
ArcSaveConfiguration(VOID)
{
	return ARC_CALL0(cfg_save);
}

struct beep_sysid *
ArcGetSystemId(VOID)
{
	return (struct beep_sysid *) ARC_CALL0(get_sysid);
}

VOID __init
ArcFlushAllCaches(VOID)
{
	ARC_CALL0(cache_flush);
}

DISPLAY_STATUS * __init ArcGetDisplayStatus(ULONG FileID)
{
	return (DISPLAY_STATUS *) ARC_CALL1(GetDisplayStatus, FileID);
}
