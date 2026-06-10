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
#include <beep/kernel.h>
#include <beep/kthread.h>
#include <beep/module.h>
#include <beep/freezer.h>
#include <beep/semaphore.h>
#include <beep/slab.h>
#include <beep/bitops.h>

#include "csr_framework_ext.h"

/*----------------------------------------------------------------------------*
 *  NAME
 *      CsrThreadSleep
 *
 *  DESCRIPTION
 *      Sleep for a given period.
 *
 *  RETURNS
 *      void
 *
 *----------------------------------------------------------------------------*/
void CsrThreadSleep(u16 sleepTimeInMs)
{
    unsigned long t;

    /* Convert t in ms to jiffies and round up */
    t = ((sleepTimeInMs * HZ) + 999) / 1000;
    schedule_timeout_uninterruptible(t);
}
EXPORT_SYMBOL_GPL(CsrThreadSleep);
