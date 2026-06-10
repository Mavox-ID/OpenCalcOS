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
/*
 * This file is conditionally built on PowerPC only.  Otherwise weak symbol
 * versions of the functions exported from here are used.
 */

#include "qib.h"

/**
 * qib_enable_wc - enable write combining for MMIO writes to the device
 * @dd: qlogic_ib device
 *
 * Nothing to do on PowerPC, so just return without error.
 */
int qib_enable_wc(struct qib_devdata *dd)
{
	return 0;
}

/**
 * qib_unordered_wc - indicate whether write combining is unordered
 *
 * Because our performance depends on our ability to do write
 * combining mmio writes in the most efficient way, we need to
 * know if we are on a processor that may reorder stores when
 * write combining.
 */
int qib_unordered_wc(void)
{
	return 1;
}
