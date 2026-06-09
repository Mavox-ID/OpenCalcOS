/*****************************************************************************

            (c) Cambridge Silicon Radio Limited 2010
            All rights reserved and confidential information of CSR

            Refer to LICENSE.txt included with this source for details
            on the license terms.

*****************************************************************************/

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
