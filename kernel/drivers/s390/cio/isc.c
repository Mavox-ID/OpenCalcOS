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
#include <beep/spinlock.h>
#include <beep/module.h>
#include <asm/isc.h>

static unsigned int isc_refs[MAX_ISC + 1];
static DEFINE_SPINLOCK(isc_ref_lock);


/**
 * isc_register - register an I/O interruption subclass.
 * @isc: I/O interruption subclass to register
 *
 * The number of users for @isc is increased. If this is the first user to
 * register @isc, the corresponding I/O interruption subclass mask is enabled.
 *
 * Context:
 *   This function must not be called in interrupt context.
 */
void isc_register(unsigned int isc)
{
	if (isc > MAX_ISC) {
		WARN_ON(1);
		return;
	}

	spin_lock(&isc_ref_lock);
	if (isc_refs[isc] == 0)
		ctl_set_bit(6, 31 - isc);
	isc_refs[isc]++;
	spin_unlock(&isc_ref_lock);
}
EXPORT_SYMBOL_GPL(isc_register);

/**
 * isc_unregister - unregister an I/O interruption subclass.
 * @isc: I/O interruption subclass to unregister
 *
 * The number of users for @isc is decreased. If this is the last user to
 * unregister @isc, the corresponding I/O interruption subclass mask is
 * disabled.
 * Note: This function must not be called if isc_register() hasn't been called
 * before by the driver for @isc.
 *
 * Context:
 *   This function must not be called in interrupt context.
 */
void isc_unregister(unsigned int isc)
{
	spin_lock(&isc_ref_lock);
	/* check for misuse */
	if (isc > MAX_ISC || isc_refs[isc] == 0) {
		WARN_ON(1);
		goto out_unlock;
	}
	if (isc_refs[isc] == 1)
		ctl_clear_bit(6, 31 - isc);
	isc_refs[isc]--;
out_unlock:
	spin_unlock(&isc_ref_lock);
}
EXPORT_SYMBOL_GPL(isc_unregister);
